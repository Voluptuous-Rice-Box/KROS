#include <stddef.h>
#include <stdint.h>
// #include "io/interrupt.h"
#include "io/test.h"

/* Hardware text mode color constants. */
enum vga_color
{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

size_t strlen(const char* str)
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 24;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c)
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if ( ++terminal_column == VGA_WIDTH )
	{
		terminal_column = 0;
		if ( ++terminal_row == VGA_HEIGHT )
		{
			terminal_row = 0;
		}
	}
}

struct cpu_state {
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
	unsigned int ebp;
	unsigned int esp;
} __attribute__((packed));

struct stack_state {
	unsigned int error_code;
	unsigned int eip;
	unsigned int cs;
	unsigned int eflags;
} __attribute__((packed));

void terminal_writestring(const char* data)
{
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		terminal_putchar(data[i]);
}

extern "C" void interrupt_handler(struct cpu_state cpu, struct stack_state stack, unsigned int interrupt) {
	if (interrupt < 10) {
		terminal_writestring("got interrupt less than 10");
	} else {
		terminal_writestring("got interrupt greater than or equal to 10");
	}
	for (int i = 0; i < 100000000; i++) {

	}
}

// Don't mangle the kernel entry point. The linker needs to know
// what this function is called to pass the address to the bootloader.
extern "C" void kmain()
{
	// set_idt_gate(0, (uint32_t) interrupt_handler_0);
	// set_idt_gate(1, (uint32_t) interrupt_handler_1);
	// set_idt_gate(2, (uint32_t) interrupt_handler_2);
	// set_idt_gate(3, (uint32_t) interrupt_handler_3);
	// set_idt_gate(4, (uint32_t) interrupt_handler_4);
	// set_idt_gate(5, (uint32_t) interrupt_handler_5);
	// set_idt_gate(6, (uint32_t) interrupt_handler_6);
	// set_idt_gate(7, (uint32_t) interrupt_handler_7);
	// set_idt_gate(8, (uint32_t) interrupt_handler_8);
	// set_idt_gate(9, (uint32_t) interrupt_handler_9);
	// set_idt_gate(10, (uint32_t) interrupt_handler_10);
	// set_idt_gate(11, (uint32_t) interrupt_handler_11);
	// set_idt_gate(12, (uint32_t) interrupt_handler_12);
	// set_idt_gate(13, (uint32_t) interrupt_handler_13);
	// set_idt_gate(14, (uint32_t) interrupt_handler_14);
	// set_idt_gate(15, (uint32_t) interrupt_handler_15);

	int y = test();
	int z = SNDUANSDUAS;

	terminal_initialize();
	terminal_writestring("welcome to my first operating system!");
	int x = 3 / 0;
	for(;;);
}
