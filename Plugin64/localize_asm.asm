EXTERN	localizeProc1ReturnAddress1	:	QWORD
EXTERN	localizeProc1ReturnAddress2	:	QWORD

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
localizeProc1 PROC
	mov		r8, [rsp + 128h - 0F8h];
	mov		r9, [rsp + 128h - 0E0h];

	cmp		r10d, 3;
	jl		JMP_B;

	lea     rax, [rsp + 128h - 0F8h];
	cmp		r9, 10h;
	cmovnb	rax, r8;

	cmp		byte ptr[rax + r10 - 3], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rax + r10 - 3], ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		byte ptr[rax + r10 - 3], ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		byte ptr[rax + r10 - 3], ESCAPE_SEQ_4;
	jz		JMP_A;

	jmp		JMP_B;

JMP_A:
	push	localizeProc1ReturnAddress1;
	ret;

JMP_B:
	cmp		r10d, 4;
	push	localizeProc1ReturnAddress2;
	ret;
localizeProc1 ENDP

;----------------------;
END