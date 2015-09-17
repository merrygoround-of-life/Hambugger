TITLE	HbgREAL10toDOUBLE Procedure	(HbgFpu_Win32.asm)

.386
.model flat, C

.code

HbgREAL10toDOUBLE	PROC,
	ipt:PTR QWORD,	; input param
	opt:PTR REAL8	; output param
					; returns nothing
							
	mov eax, ipt
	fld TBYTE PTR [eax]
	mov eax, opt
	fstp REAL8 PTR [eax]		
	ret
	
HbgREAL10toDOUBLE	ENDP
END
