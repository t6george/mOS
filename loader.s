.set MAGIC, 0x1badb002
.set FLAGS, 3
.set CHECKSUM, -(FLAGS+MAGIC)

.section .multiboot

.section .text
.extern kernelEntry
.global loader

loader:
	mov $kernel_stack, %esp
	push %eax
	push %ebx
	call kernelEntry	

_stop:
	cli
	hlt
	jmp _stop

.section .bss
.space (1 << 21) #2 MB for stack
kernel_stack: 
