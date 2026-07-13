section .text
	global outb
	global inb
outb:
	mov al, [esp+8]
	mov dx, [esp+4]
	out dx, al
	ret

inb:
	mov dx, [esp+4] ; Grab the 16-bit port number from the stack
	in al, dx       ; Read 1 byte from port DX directly into the AL register
	ret             

