global loader

MAGIC_NUMBER equ 0x1BADB002
FLAGS	     equ 0x0
CHECKSUM     equ -(MAGIC_NUMBER + FLAGS)
STACK_SIZE   equ 0x1000

section .text:
align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

loader:
	mov esp, kernel_stack + STACK_SIZE

	; using cdecl calling convention
	
	mov eax, 0xCAFEBABE
	call kmain

.loop:
	jmp .loop

section .bss
align 4
	kernel_stack:
		resb STACK_SIZE
