BUILD=build
ISO=iso

all: $(BUILD)/kernel.elf

$(BUILD):
	mkdir -p $(BUILD)

# ASM ========================================================================
$(BUILD)/kernel_entry.o: kernel/arch/kernel_entry.asm | $(BUILD)
	nasm -f elf32 $< -o $@

# CORE =======================================================================
$(BUILD)/kernel.o: kernel/core/kernel.c | $(BUILD)
	gcc -m32 -ffreestanding -c $< -o $@

# VGA ========================================================================
$(BUILD)/vga.o: kernel/drivers/video/vga.c | $(BUILD)
	gcc -m32 -ffreestanding -c $< -o $@

# LINK =======================================================================
$(BUILD)/kernel.elf: $(BUILD)/kernel_entry.o $(BUILD)/kernel.o $(BUILD)/vga.o
	ld -m elf_i386 -T linker.ld -o $@ $^

# ISO ========================================================================
iso: $(BUILD)/kernel.elf
	mkdir -p $(ISO)/boot/grub
	cp $< $(ISO)/boot/
	cp os/grub.cfg $(ISO)/boot/grub/grub.cfg
	grub-mkrescue -o os.iso $(ISO)

run: iso
	qemu-system-i386 -cdrom os.iso

clean:
	rm -rf $(BUILD) $(ISO) os.iso
