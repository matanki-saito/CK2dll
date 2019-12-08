EXTERN	unkProc1ReturnAddress	:	QWORD

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

.CODE
unkProc1 PROC
	cmp		byte ptr [rax + rdi], ESCAPE_SEQ_1;
	jz		JMP_A;
			
	cmp		byte ptr [rax + rdi], ESCAPE_SEQ_2;
	jz		JMP_B;

	cmp		byte ptr [rax + rdi], ESCAPE_SEQ_3;
	jz		JMP_C;

	cmp		byte ptr [rax + rdi], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx	eax, byte ptr [rax + rdi];
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr [rax + rdi + 1];
	jmp		JMP_F;
JMP_B:
	movzx	eax, word ptr [rax + rdi + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;
JMP_C:
	movzx	eax, word ptr [rax + rdi + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;
JMP_D:
	movzx	eax, word ptr [rax + rdi + 1];
	add		eax, SHIFT_4;
	jmp		JMP_F;

JMP_F:
	add		edi, 2;
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_E;
	mov		eax, NOT_DEF;

JMP_E:
	mov		r10, qword ptr [r13 + rax * 8 +0E8h];

	test	r10,r10;
	push	unkProc1ReturnAddress;
	ret;
unkProc1 ENDP

END