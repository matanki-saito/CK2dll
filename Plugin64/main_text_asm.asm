EXTERN mainTextProc1ReturnAddress: QWORD
EXTERN mainTextProc2ReturnAddress: QWORD
EXTERN mainTextProc2BufferAddress1: QWORD
EXTERN mainTextProc2BufferAddress2: QWORD
EXTERN mainTextProc3ReturnAddress1: QWORD
EXTERN mainTextProc3ReturnAddress2: QWORD
EXTERN mainTextProc4ReturnAddress: QWORD

ESCAPE_SEQ_1	=	10h
ESCAPE_SEQ_2	=	11h
ESCAPE_SEQ_3	=	12h
ESCAPE_SEQ_4	=	13h
LOW_SHIFT		=	0Fh
HIGH_SHIFT		=	9h
SHIFT_2			=	LOW_SHIFT
SHIFT_3			=	900h
SHIFT_4			=	8F1h
NO_FONT			=	98Fh
NOT_DEF			=	2026h

;temporary space for code point
.DATA
	mainTextProc2TmpCharacter	DD	0

.CODE
mainTextProc1 PROC
	movsxd	rax, ebx;

	cmp		byte ptr[rax + r12], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rax + r12], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rax + r12], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rax + r12], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx	ecx, byte ptr [rax+r12];
	jmp		JMP_E;

JMP_A:
	movzx	ecx, word ptr[rax + r12 + 1];
	jmp		JMP_F;

JMP_B:
	movzx	ecx, word ptr[rax + r12 + 1];
	sub		ecx, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	ecx, word ptr[rax + r12 + 1];
	add		ecx, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	ecx, word ptr[rax + r12 + 1];
	add		ecx, SHIFT_4;

JMP_F:
	movzx	ecx, cx;
	add		ebx, 2;
	cmp		ecx, NO_FONT;

	ja		JMP_E;
	mov		ecx, NOT_DEF;
JMP_E:
	mov		r12, qword ptr [rsi+rcx*8+0E8h];

	test    r12, r12;
	push	mainTextProc1ReturnAddress;
	ret;
mainTextProc1 ENDP

;-------------------------------------------;

mainTextProc2 PROC
	movsxd  rax, edi;
	mov		r9, mainTextProc2BufferAddress1;
	movzx   ecx, byte ptr [rax+r9];
	movsxd  rax, r14d;
	mov		r11, mainTextProc2BufferAddress2;
	mov		byte ptr[rax+r11], cl;
	inc     r14d;

	cmp		cl, ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		cl, ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		cl, ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		cl, ESCAPE_SEQ_4;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rdi+r9+1];
	mov		word ptr [r14+r11], ax;
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rdi+r9+1];
	mov		word ptr [r14+r11], ax;
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr [rdi+r9+1];
	mov		word ptr [r14+r11], ax;
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr [rdi+r9+1];
	mov		word ptr [r14+r11], ax;
	add		eax, SHIFT_4;

JMP_F:
	movzx	eax, ax;
	add		r14d, 2;
	add		edi,2;
	cmp		eax, NO_FONT;

	ja		JMP_E;
	mov		eax, NOT_DEF;

JMP_E:
	mov		mainTextProc2TmpCharacter, eax;
	push	mainTextProc2ReturnAddress;
	ret;
mainTextProc2 ENDP

;-------------------------------------------;

mainTextProc3 PROC
	cmp		dword ptr [rbp-6Ch], 0;
	jnz		JMP_A;
	jmp		JMP_B;

JMP_A:
	cmp		mainTextProc2TmpCharacter, 00FFh;
	ja		JMP_B;

	push	mainTextProc3ReturnAddress2;
	ret;
	
JMP_B:
	lea		eax, [r15+rbx*2];
	cmp		eax, [rbp-78h];

	push	mainTextProc3ReturnAddress1;
	ret;

mainTextProc3 ENDP

;-------------------------------------------;

mainTextProc4 PROC
	; check code point saved proc1
	cmp		mainTextProc2TmpCharacter, 00FFh;
	ja		JMP_A;

	movzx	eax, cl;
	jmp		JMP_B;

JMP_A:
	mov		eax, mainTextProc2TmpCharacter;

JMP_B:
	mov		r9, qword ptr[rsi+rax*8+0E8h];
	test	r9, r9;

	push	mainTextProc4ReturnAddress;
	ret;
mainTextProc4 ENDP

END