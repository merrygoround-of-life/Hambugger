TITLE	HbgREAL10toDOUBLE Procedure	(HbgFpu_x64.asm)

.code

HbgREAL10toDOUBLE	PROC,
	ipt:PTR QWORD,	; input param
	opt:PTR REAL8	; output param
					; returns nothing
							
	mov rax, ipt
	fld TBYTE PTR [rax]
	mov rax, opt
	fstp REAL8 PTR [rax]		
	ret
	
HbgREAL10toDOUBLE	ENDP
END
