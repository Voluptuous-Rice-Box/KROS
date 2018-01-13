; nasm directive, specifying that this OS is 32-bits
bits 32

section .text
; multiboot header, required by grub
	align 4
	dd 0x1BADB002            ; magic
	dd 0x00                  ; flags
	dd - (0x1BADB002 + 0x00) ; checksum. m+f+c should be zero

; this specifies code entry points for the linker (see linker.ld)
global start
global halt_os

; the linker will resolve the address of our main kernel function
extern kmain

; bootloader code
start:
	cli
	mov esp, kernel_stack + KERNEL_STACK_SIZE ; stack grows upward
	call kmain
	jmp halt_os

halt_os:
	hlt

KERNEL_STACK_SIZE equ 8192

section .bss
align 4
kernel_stack:
	resb KERNEL_STACK_SIZE
