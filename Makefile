.PHONY: clean iso

iso:
	# Compile the bootloader
	nasm -f elf src/bootloader.asm -o bootloader.o

	# Compile the kernel
	g++ -m32 -c src/kernel.cpp -o kernel.o -ffreestanding -fno-exceptions -fno-rtti

	# Build the kernel executable. The linker helps the bootloader
	# find the entry point (our kernel main function). The kernel
	# must be placed in /iso/boot/ for grub-mkrescue to build an iso.
	# Note that the executable MUST be called "kern", as that is the
	# executable that GRUB will look for when the OS is loaded.
	gcc -m32 bootloader.o kernel.o -T src/linker.ld -o iso/boot/kern -nostdlib -nodefaultlibs -lgcc

	# Build the final iso
	grub-mkrescue iso --output=os.iso -d /usr/lib/grub/i386-pc

clean:
	rm -f *.o *.iso iso/boot/kern
