#include <stdint.h>
#include "idt.h"
/* ISRs definidos en isr.asm */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr13();
extern void isr14();

/* La IDT tiene 256 entradas posibles (0-255) */
static idt_entry_t idt[256];
static idt_descriptor_t idt_desc;

/* Función en assembly que carga la IDT con lidt */
extern void idt_load(idt_descriptor_t* desc);

/* Registra un handler en la IDT */
void idt_set_entry(u8 num, u32 base, u16 selector, u8 flags) {
    idt[num].base_low  = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector  = selector;
    idt[num].zero      = 0;
    idt[num].flags     = flags;
}

void idt_init() {
    idt_desc.limit = (sizeof(idt_entry_t) * 256) - 1;
    idt_desc.base  = (uintptr_t) &idt;

    idt_set_entry(0,  (u32)(uintptr_t)isr0,  0x08, 0x8E);
    idt_set_entry(1,  (u32)(uintptr_t)isr1,  0x08, 0x8E);
    idt_set_entry(2,  (u32)(uintptr_t)isr2,  0x08, 0x8E);
    idt_set_entry(3,  (u32)(uintptr_t)isr3,  0x08, 0x8E);
    idt_set_entry(4,  (u32)(uintptr_t)isr4,  0x08, 0x8E);
    idt_set_entry(5,  (u32)(uintptr_t)isr5,  0x08, 0x8E);
    idt_set_entry(6,  (u32)(uintptr_t)isr6,  0x08, 0x8E);
    idt_set_entry(7,  (u32)(uintptr_t)isr7,  0x08, 0x8E);
    idt_set_entry(8,  (u32)(uintptr_t)isr8,  0x08, 0x8E);
    idt_set_entry(13, (u32)(uintptr_t)isr13, 0x08, 0x8E);
    idt_set_entry(14, (u32)(uintptr_t)isr14, 0x08, 0x8E);

    idt_load(&idt_desc);
}