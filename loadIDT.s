section .text
	global loadIDT
loadIDT:
	mov eax, [esp + 4]
	lidt [eax]
	ret
