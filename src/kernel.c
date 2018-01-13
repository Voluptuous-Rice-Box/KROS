#include <stddef.h>
#include <stdint.h>

#include "io/terminal.h"

// Don't mangle the kernel entry point. The linker needs to know
// what this function is called to pass the address to the bootloader.
extern void kmain()
{
	terminal_initialize();
	terminal_write("welcome to my first operating system!");
	terminal_write("welcome to my first operating system!");
	terminal_write("welcome to my first operating system!");
	terminal_write("welcome to my first operating system!");
	terminal_write("welcome to my first operating system!");
	terminal_write("welcome to my first operating system!");
	terminal_write("welcome to my first operating system!");
	for(;;);
}
