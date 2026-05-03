; kernel/arch/isr.asm

extern isr_handler

%macro ISR 1
global isr%1

isr%1:
    cli ; desactivamos interrupciones
    pusha ; guardamos registros
    push %1 ; pasamos el numero del vector a isr_handler
    call isr_handler ; llamamos a la funcion en C
    add esp, 4 ; limpiamos el argumento del stack
    popa ; restauramos registros
    sti ; rehabilitamos interrupciones
    iret ; regresa ( restauramos EIP, CS y EFLAGS )
%endmacro

ISR 0   ; Division by Zero
ISR 1   ; Debug
ISR 2   ; Non-Maskable Interrupt
ISR 3   ; Breakpoint
ISR 4   ; Overflow
ISR 5   ; Bound Range Exceeded
ISR 6   ; Invalid Opcode
ISR 7   ; Device Not Available
ISR 8   ; Double Fault
ISR 13  ; General Protection Fault
ISR 14  ; Page Fault

