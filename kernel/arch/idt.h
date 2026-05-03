#ifndef IDT_H
#define IDT_H

#include "../include/types.h"

typedef struct {
    u16 base_low;
    u16 selector;
    u8 zero;
    u8 flags;
    u16 base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) idt_descriptor_t;

void idt_init();

#endif