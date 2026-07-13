extern kernel_main

global loader ;makes loader visible to the linker by globalising it

	KERNEL_STACK equ 1048576 ;Reserve a huge space for the stack. 
	USER_STACK equ 1048576 ;Reserve space for ring 3 stack. 

	MAGIC_NUM equ 0x1BADB002 ;A magic hardcoded num GRUB needs to work
	FLAGS equ 0X00000000 ;Flags can be any value as long as CHECKSUM + FLAGS + MAGIC NUMBER is 0. It is set 0x0 here for the sake of convenience 
	CHECKSUM equ -(MAGIC_NUM) ;CHECKSUM is just the -ve of MAGIC NUMBER
	

	global kernel_stack_top
	global user_stack_top

	kernel_stack_top: equ kernel_stack + KERNEL_STACK ; Globalize kernel stack top for TSS to see far later on
	user_stack_top: equ user_stack + USER_STACK ;Same here 

section .bss
align 4 ;align 4 cause that's how we roll

kernel_stack:
	resb KERNEL_STACK ;reserve the bytes for Kernel stack which we just set to 1,048,576 a few lines ago

user_stack:
	resb USER_STACK 

section .text 

	dd MAGIC_NUM ;define double word (32 bit) MAGIC NUMBER
	dd FLAGS ;define double word for FLAGS...
	dd CHECKSUM ; ...and CHECKSUM

loader:
	mov esp, kernel_stack + KERNEL_STACK ;Point the stack buffer to the address Hex 2,096,576, idk, maybe it points to some other address, somebody can correct me if I am wrong. Also THIS SETS UP THE STACK WOOHOOO

	call kernel_main ;call my c++ function   

end: 
	hlt ;execute halt.boy does it feel good to write a priveliged instruction without the OS screaming at me. F Windows. 
	jmp end 
