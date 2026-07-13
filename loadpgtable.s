section .text 
	global loadpgtable
loadpgtable: 
	push ebp
	mov ebp, esp 
	mov eax, cr0 
	or eax, 0x80000000 ;Maps to binary- 10000000000000000000000000000000, Also the 31st or the leftmost bit sets the flag of CR0.PG
	mov cr0, eax 
	mov esp, ebp 
	pop ebp 
	ret
