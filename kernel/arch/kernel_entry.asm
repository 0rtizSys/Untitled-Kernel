section .multiboot
align 4
    dd 0x1BADB002       ; Magic number de Multiboot
    dd 0x0              ; Flags
    dd -(0x1BADB002 + 0x0) ; Checksum

section .bss
align 16
stack_bottom:
    resb 16384          ; Reserva 16KB para el stack
stack_top:

section .text
global _start
extern kmain

_start:
    cli                 ; Deshabilita interrupciones al arrancar

    ; Configura el stack — sin esto kmain puede corromper memoria
    mov esp, stack_top

    ; Carga la GDT
    lgdt [gdt_descriptor]

    ; Recarga los segmentos con los nuevos selectores de la GDT
    mov ax, 0x10        ; 0x10 = segmento de datos (entrada 2 de la GDT)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Far jump para recargar CS con el segmento de código (0x08 = entrada 1)
    jmp 0x08:flush_cs
flush_cs:

    call kmain

.hang:
    hlt
    jmp .hang

; ─── GDT ───────────────────────────────────────────
section .data
gdt_start:

; Entrada 0 — Null descriptor (obligatorio, la CPU lo requiere)
gdt_null:
    dd 0x0
    dd 0x0

; Entrada 1 — Segmento de código (0x08)
gdt_code:
    dw 0xFFFF           ; Límite bits 0-15
    dw 0x0              ; Base bits 0-15
    db 0x0              ; Base bits 16-23
    db 10011010b        ; Acceso: presente, anillo 0, ejecutable, legible
    db 11001111b        ; Flags: 32bits, granularidad 4KB + límite bits 16-19
    db 0x0              ; Base bits 24-31

; Entrada 2 — Segmento de datos (0x10)
gdt_data:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10010010b        ; Acceso: presente, anillo 0, escribible
    db 11001111b
    db 0x0

gdt_end:

; Descriptor que le pasamos a lgdt — tamaño y dirección de la GDT
gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Tamaño en bytes - 1
    dd gdt_start                ; Dirección de la GDT

global idt_load
idt_load:
    mov eax, [esp + 4]  ; Toma el puntero al descriptor
    lidt [eax]          ; Carga la IDT
    ret