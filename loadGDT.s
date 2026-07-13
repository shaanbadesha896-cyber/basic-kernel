section .text
	global loadGDT
loadGDT:

	mov ebx, [esp+4]
	lgdt [ebx] 
	

	; jmp SELECTOR:offset
	; 0x08 is the offset of Kernel Code Segment in the GDT
	; $ is the current address (don't move, just reload the segment)
	
	jmp 0x08:reload_segments ; FAR jump

reload_segments:

	;Reload Data Segments (DS, SS, ES, etc.)
	mov bx, 0x10  ; Offset of your Data Segment
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx
	mov ss, bx

	ret	
