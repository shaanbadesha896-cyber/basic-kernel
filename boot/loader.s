global loader

	MAGIC_NUM equ 0x1BADB002 
	FLAGS equ 0X00000000
	CHECKSUM equ -(MAGIC_NUM)

section .text 

	dd MAGIC_NUM
	dd FLAGS
	dd CHECKSUM 

loader:
	mov eax, 0xCAFEBABE

.loop: 
	jmp .loop
