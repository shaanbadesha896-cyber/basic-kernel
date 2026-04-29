out 0x3D4, 14
out 0x3D5, 0x00
out 0x3D4, 15
out 0x3D5, 0x50

global outb


outb:
	mov al, [esp+8]
	mov dx, [esp+4]
	out dx, al
	ret

