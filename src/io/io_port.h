#ifndef IO_PORT_H
#define IO_PORT_H

/* The I/O ports */
#define FRAME_BUF_COMMAND_PORT 0x3D4
#define FRAME_BUF_DATA_PORT 0x3D5
/* The I/O port commands */
#define FRAME_BUF_HIGH_BYTE_COMMAND 14
#define FRAME_BUF_LOW_BYTE_COMMAND 15

/** outb:
* Sends the given data to the given I/O port. Defined in io.s
*
* @param port The I/O port to send the data to
* @param data The data to send to the I/O port
*/
extern void io_port_write(unsigned short port, unsigned char data);


/** fb_move_cursor:
* Moves the cursor of the framebuffer to the given position
*
* @param pos The new position of the cursor
*/
void frame_buffer_move_cursor(unsigned short pos) {
	io_port_write(FRAME_BUF_COMMAND_PORT, FRAME_BUF_HIGH_BYTE_COMMAND);
	io_port_write(FRAME_BUF_DATA_PORT, ((pos >> 8) & 0x00FF));
	io_port_write(FRAME_BUF_COMMAND_PORT, FRAME_BUF_LOW_BYTE_COMMAND);
	io_port_write(FRAME_BUF_DATA_PORT, pos & 0x00FF);
}

#endif /* IO_PORT_H */
