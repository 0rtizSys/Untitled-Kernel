#include "../drivers/video/vga.h"
#include "../arch/idt.h"

void kmain(){
    vga_clear();
    idt_init();
    vga_write("Loading Kernel... [OK]\n", VGA_COLOR(VGA_WHITE, VGA_BLUE));
    vga_write("Loading VGA Video Drivers... [OK]\n", VGA_COLOR(VGA_WHITE, VGA_BLUE));
    while (1);
}