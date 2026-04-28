global loader

	KERNEL_STACK equ 1048576 

	MAGIC_NUM equ 0x1BADB002 
	FLAGS equ 0X00000000
	CHECKSUM equ -(MAGIC_NUM)

section .bss
align 4
kernel_stack:
	reb KERNEL_STACK

section .text 

	dd MAGIC_NUM
	dd FLAGS
	dd CHECKSUM 

loader:
	mov eax, 0xCAFEBABE
	mov esp, kernel_stack + KERNEL_STACK

.loop: 
	jmp .loop
