.PHONY: clean iso

iso:
	# TODO(valakuzhy): automatically include all c files in src
	# Compile the bootloader
	nasm -f elf src/bootloader.asm -o bootloader.o

	# Compile the kernel
	gcc -m32 -c src/kernel.c -o kernel.o -ffreestanding -fno-exceptions -fno-rtti
	gcc -m32 -c src/io/terminal.c -o terminal.o -ffreestanding -fno-exceptions -fno-rtti
	gcc -m32 -c src/error.c -o error.o -ffreestanding -fno-exceptions -fno-rtti

	# Build the kernel executable. The linker helps the bootloader
	# find the entry point (our kernel main function). The kernel
	# must be placed in /iso/boot/ for grub-mkrescue to build an iso.
	# Note that the executable MUST be called "kern", as that is the
	# executable that GRUB will look for when the OS is loaded.
	gcc -m32 bootloader.o error.o kernel.o terminal.o -T src/linker.ld -o iso/boot/kern -nostdlib -nodefaultlibs -lgcc

	# Build the final iso
	grub-mkrescue iso --output=os.iso -d /usr/lib/grub/i386-pc

clean:
	rm -f *.o *.iso iso/boot/kern
