extern div_by_zero 

section .text
	global isr0
isr0: 
	pusha ;push all the general purpose regs
	push ds
	push es
	push fs
	push gs

	push esp
	call div_by_zero
	add esp, 4

	pop gs
	pop fs
	pop es
	pop ds
	popa 

	iret
