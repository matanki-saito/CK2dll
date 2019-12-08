EXTERN mainTextAdjustmentProc1ReturnAddress: QWORD
EXTERN mainTextAdjustmentProc2ReturnAddress1: QWORD
EXTERN mainTextAdjustmentProc2ReturnAddress2: QWORD

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
	mainTextAdjustmentProc1TmpCharacter	DD	0

.CODE
mainTextAdjustmentProc1 PROC
	cmp		byte ptr[rax + rdx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rax + rdx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rax + rdx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rax + rdx], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx	eax, byte ptr [rax + rdx];
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rax + rdx + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rax + rdx + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rax + rdx + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rax + rdx + 1];
	add		eax, SHIFT_4;

JMP_F:
	movzx	eax, ax;
	cmp		eax, NO_FONT;

	ja		JMP_E;
	mov		eax, NOT_DEF;
JMP_E:
	mov		mainTextAdjustmentProc1TmpCharacter, eax;

	mov		r15, qword ptr [r11 + rax * 8 + 0E8h];
	test    r15, r15;
	push	mainTextAdjustmentProc1ReturnAddress;
	ret;
mainTextAdjustmentProc1 ENDP

;-------------------------------------------;

mainTextAdjustmentProc2 PROC
	cmp		mainTextAdjustmentProc1TmpCharacter, 0FFh;
	jle		JMP_A;
	add		edi,2;

JMP_A:
	mov		mainTextAdjustmentProc1TmpCharacter, 0;
	inc		edi;
	mov		r9, qword ptr [rbx+10h];
	cmp		edi, r9d;
	jge		JMP_B;
	mov		r10d, dword ptr [rbp + 3Fh + 38h];
	mov		r11, qword ptr [rbp + 3Fh + 10h];

	push	mainTextAdjustmentProc2ReturnAddress1;
	ret;

JMP_B:
	push	mainTextAdjustmentProc2ReturnAddress2;
	ret;
mainTextAdjustmentProc2 ENDP

END