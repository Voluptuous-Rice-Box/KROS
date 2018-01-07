; nasm directive, specifying that this OS is 32-bits
bits 32

section .text
; multiboot header, required by grub
	align 4
	dd 0x1BADB002            ; magic
	dd 0x00                  ; flags
	dd - (0x1BADB002 + 0x00) ; checksum. m+f+c should be zero

; this specifies the code entry point for the linker (see linker.ld)
global start

; the linker will resolve the address of our main kernel function
extern kmain

; bootloader code
start:
	cli
	mov esp, kernel_stack + KERNEL_STACK_SIZE ; stack grows upward
	call kmain
	hlt

; generic interrupt handler code
%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	push dword 0	; push 0 as error code
	push dword %1	; push the interrup number
	jmp common_interrupt_handler
%endmacro

%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	push dword %1	; push the interrup number
	jmp common_interrupt_handler
%endmacro

extern interrupt_handler
common_interrupt_handler:
	; save all registers
	push eax
	push ebx
	push ecx
	push edx
	push ebp

	call interrupt_handler

	; restore all registers
	pop ebp
	pop edx
	pop ecx
	pop ebx
	pop eax

	; restore the esp
	add esp, 8

	; return to the code that got interrupted
	iret

; create generic interrupt handlers
no_error_code_interrupt_handler 0
no_error_code_interrupt_handler 1
no_error_code_interrupt_handler 2
no_error_code_interrupt_handler 3
no_error_code_interrupt_handler 4
no_error_code_interrupt_handler 5
no_error_code_interrupt_handler 6
error_code_interrupt_handler 7
error_code_interrupt_handler 8
error_code_interrupt_handler 9
error_code_interrupt_handler 10
error_code_interrupt_handler 11
error_code_interrupt_handler 12
error_code_interrupt_handler 13
error_code_interrupt_handler 14
error_code_interrupt_handler 15


KERNEL_STACK_SIZE equ 8192

section .bss
align 4
kernel_stack:
	resb KERNEL_STACK_SIZE
