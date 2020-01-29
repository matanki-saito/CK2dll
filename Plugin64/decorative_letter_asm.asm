EXTERN	decorativeLetterProc1ReturnAddress	:	QWORD
EXTERN	decorativeLetterProc2CallAddress	:	QWORD
EXTERN	decorativeLetterProc2ReturnAddress	:	QWORD
EXTERN	decorativeLetterProc3ReturnAddress	:	QWORD

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
decorativeLetterProc1 PROC
	lea		rdx, [rbp + 19B0h - 780h];
	lea		rcx, [rbp + 19B0h - 16D8h];

	cmp		qword ptr[rcx + 10h], 10h;
	jb		JMP_A;
	mov		rcx, [rcx];

JMP_A:
	mov		cl, byte ptr [rcx];

	cmp		cl, ESCAPE_SEQ_1;
	jz		JMP_B;

	cmp		cl, ESCAPE_SEQ_2;
	jz		JMP_B;

	cmp		cl, ESCAPE_SEQ_3;
	jz		JMP_B;

	cmp		cl, ESCAPE_SEQ_4;
	jz		JMP_B;

	jmp		JMP_C;

JMP_B:
	mov		r9d,3;
	jmp		JMP_D;

JMP_C:
	mov		r9d,1;

JMP_D:
	xor		r8d, r8d;
	lea		rcx, [rbp + 19B0h - 16D8h]; Œ³‚É–ß‚·

	push	decorativeLetterProc1ReturnAddress;
	ret;
decorativeLetterProc1 ENDP

;----------------------;

decorativeLetterProc2 PROC
	lea		rsi, [rax + rdi];
	movzx	eax, byte ptr [rax + rdi];
	cmp		al, 0FEh;
	jz		JMP_B;
	cmp		al, ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_4;
	jz		JMP_A;

	movsx	ecx, al;
	call	decorativeLetterProc2CallAddress;
	mov		byte ptr [rsi], al;
	jmp		JMP_C;

JMP_B:
	mov		byte ptr [rsi], 0DEh;
	jmp		JMP_C;

JMP_A:
	add		ebx, 2;

JMP_C:
	inc		ebx;
	mov		eax, ebx;
	cmp		byte ptr [rbx + rdi], 0;

	push	decorativeLetterProc2ReturnAddress;
	ret;
decorativeLetterProc2 ENDP

;----------------------;

decorativeLetterProc3 PROC
	mov     rbx, rax;
	mov		r9d, dword ptr [rbp + 19B0h - 16C8h];

	lea		rcx, [rbp + 19B0h - 16D8h];
	cmp		dword ptr[rcx + 10h], 10h;
	jb		JMP_A;
	mov		rcx, [rcx];

JMP_A:
	mov		al, byte ptr [rcx];
	cmp		al, ESCAPE_SEQ_1;
	jz		JMP_B;
	cmp		al, ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		al, ESCAPE_SEQ_3;
	jz		JMP_B;
	cmp		al, ESCAPE_SEQ_4;
	jz		JMP_B;
	jmp		JMP_C;

JMP_B:
	mov		r8d, 3;
	jmp		JMP_D;

JMP_C:
	mov		r8d, 1;

JMP_D:
	lea		rdx, [rbp + 19B0h - 760h];
	lea		rcx, [rbp + 19B0h - 16D8h];

	push	decorativeLetterProc3ReturnAddress;
	ret;
decorativeLetterProc3 ENDP

END