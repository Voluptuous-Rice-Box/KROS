#include <stddef.h>
#include <stdint.h>

#include "terminal.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 24;
static uint16_t* TERMINAL_BUFFER = (uint16_t*) 0xB8000;

static size_t current_terminal_row;
static size_t current_terminal_column;
static uint8_t terminal_color;

/* PRIVATE FUNCTIONS */

uint16_t make_vga_entry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

size_t terminal_buffer_idx(size_t x, size_t y) {
    return y * VGA_WIDTH + x;
}

/* END PRIVATE FUNCTIONS */

// TODO(valakuzhy): Create a terminal class, and call these functions on it.

uint8_t make_terminal_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

// TODO(valakuzhy): Move this to a string util library
size_t strlen(const char* str) {
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

void terminal_initialize() {
	current_terminal_row = 0;
	current_terminal_column = 0;
	terminal_color = make_terminal_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	for ( size_t y = 0; y < VGA_HEIGHT; y++ ) {
		for ( size_t x = 0; x < VGA_WIDTH; x++ ) {
			const size_t idx = terminal_buffer_idx(x,y);
			TERMINAL_BUFFER[idx] = make_vga_entry(' ', terminal_color);
		}
	}
}

void terminal_set_color(uint8_t color) {
	terminal_color = color;
}

void terminal_put_entry_at(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = terminal_buffer_idx(x,y);
	TERMINAL_BUFFER[index] = make_vga_entry(c, color);
}

void terminal_putchar(char c) {
	terminal_put_entry_at(c, terminal_color, current_terminal_column, current_terminal_row);
	if ( ++current_terminal_column == VGA_WIDTH ) {
		current_terminal_column = 0;
		if ( ++current_terminal_row == VGA_HEIGHT ) {
			current_terminal_row = 0;
		}
	}
}

void terminal_write(const char* data) {
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		terminal_putchar(data[i]);
}

void terminal_write_int(int n) {
	if (n < 0) {
		terminal_putchar('-');
		n = n * -1;
	}

	// Can shorten this step when we implement log
	int num_digits = 0;
	int tmp = n;
	do {
		num_digits++;
		tmp = tmp / 10;
	} while (tmp > 0);

	do {
		// Can shorten this step when we implement pow
		int base = 1;
		for (int i = 0; i < num_digits - 1; i++) {
			base = base * 10;
		}
		char digit = (n / base);

		terminal_putchar('0' + digit);
		n = n - (digit * base);
		num_digits--;
	} while (num_digits > 0);
}
