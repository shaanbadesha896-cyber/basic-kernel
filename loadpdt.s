section .text 
	global loadpdt
loadpdt:
	push ebp
	mov ebp, esp
	mov eax, [esp + 8] ;mov the address of the pdt in the eax
	mov cr3, eax ;CR3 contains the physical address of the base of the paging-structure hierarchy 
	mov esp, ebp
	pop ebp
	ret
