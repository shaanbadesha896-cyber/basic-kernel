extern syscaller


ENOSYS equ 38

section .text
        global isr128
isr128:
	push eax
	
	push gs
	push fs
	push es
	push ds
	push dword -ENOSYS
	
	push ebp
	push edi
	push esi
	push edx
	push ecx
	push ebx
	push esp
	
	call syscaller
	
	add esp, 4
	
	pop ebx
	pop ecx
	pop edx
	pop esi
	pop edi
	pop ebp	

	pop ds
	pop es
	pop fs
	pop gs
	
	add esp, 4

	pop eax	
	iretd
