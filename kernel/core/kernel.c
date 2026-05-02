#include "../drivers/video/vga.h"

void kmain(){
    vga_clear();
    vga_write("Loading Kernel... [OK]\n", VGA_COLOR(VGA_WHITE, VGA_BLUE));
    vga_write("Loading VGA Video Drivers... [OK]\n", VGA_COLOR(VGA_WHITE, VGA_BLUE));
    
    while (1);
}