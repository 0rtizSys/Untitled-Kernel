#include "../drivers/video/vga.h"
#include <endian.h>

static const char* exception_messages[] = {
    "Division by Zero",          // 0
    "Debug",                     // 1
    "Non-Maskable Interrupt",    // 2
    "Breakpoint",                // 3
    "Overflow",                  // 4
    "Bound Range Exceeded",      // 5
    "Invalid Opcode",            // 6
    "Device Not Available",      // 7
    "Double Fault",              // 8
    "Unknown",                   // 9
    "Unknown",                   // 10
    "Unknown",                   // 11
    "Unknown",                   // 12
    "General Protection Fault",  // 13
    "Page Fault"                 // 14
};

void isr_handler(u32 vector){
    vga_clear();
    vga_write("KERNEL PANIC!\n", VGA_COLOR(VGA_WHITE, VGA_RED));

    if (vector < 15){
        vga_write(exception_messages[vector], VGA_COLOR(VGA_WHITE, VGA_RED));
    }else {
        vga_write("Unknow exception", VGA_COLOR(VGA_WHITE, VGA_RED));
    }

    asm volatile("cli; hlt");
}