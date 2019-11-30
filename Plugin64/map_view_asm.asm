EXTERN	mapViewProc1ReturnAddress	:	QWORD
EXTERN	mapViewProc2ReturnAddress	:	QWORD
EXTERN	mapViewProc3ReturnAddress	:	QWORD
EXTERN	mapViewProc3CallAddress		:	QWORD
EXTERN	mapViewProc3CallAddress		:	QWORD

ESCAPE_SEQ_1	=	10h
ESCAPE_SEQ_2	=	11h
ESCAPE_SEQ_3	=	12h
ESCAPE_SEQ_4	=	13h
LOW_SHIFT		=	0Eh
HIGH_SHIFT		=	9h
SHIFT_2			=	LOW_SHIFT
SHIFT_3			=	900h
SHIFT_4			=	8F2h
NO_FONT			=	98Fh
NOT_DEF			=	2026h

; temporary space for code point
.DATA
	mapViewProc3TmpCharacterAddress	DQ	0

.CODE
mapViewProc1 PROC
	cmp		byte ptr [rax+rsi], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rax+rsi], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [rax+rsi], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [rax+rsi], ESCAPE_SEQ_4;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr [rax + rsi + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr [rax + rsi + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr [rax + rsi + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr [rax + rsi + 1];
	add		eax, SHIFT_4;

JMP_F:
	add		esi, 2;
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;
	jmp		JMP_G;

JMP_E:
	movzx	eax, byte ptr [rax +rsi];

JMP_G:
	mov		r11, qword ptr [rdi + rax * 8 + 0E8h];

	;issue-161
	cmp		r11,0;
	jnz		JMP_N;
	mov		eax, NOT_DEF;
	mov     r11, qword ptr [ rdi + rax * 8 + 0E8h];

JMP_N:
	test	r11, r11;

	push	mapViewProc1ReturnAddress;
	ret;
mapViewProc1 ENDP

;-------------------------------------------;

mapViewProc2 PROC
	lea     r9, [r12 + 100h];

	cmp		byte ptr[rax + r12], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rax + r12], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rax + r12], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rax + r12], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx	eax, byte ptr[rax + r12];
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rax + r12 + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rax + r12 + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rax + r12 + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rax + r12 + 1];
	add		eax, SHIFT_4;

JMP_F:
	add		r12, 2;

	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_E;

JMP_G:
	mov		eax, NOT_DEF;

JMP_E:
	mov		rcx, qword ptr [rbp + 330h];
	mov		r15, qword ptr [rcx + rax * 8 + 0E8h]

	push	mapViewProc2ReturnAddress;
	ret;
mapViewProc2 ENDP

;-------------------------------------------;

mapViewProc3 PROC
    mov		qword ptr[rbp-8],0;

	cmp		byte ptr [r12 + rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [r12 + rax], ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		byte ptr [r12 + rax], ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		byte ptr [r12 + rax], ESCAPE_SEQ_4;
	jz		JMP_A;

	movzx	r8d, byte ptr[r12 + rax];
	mov     edx, 1;
	lea     rcx, [rbp-8];
	call	mapViewProc3CallAddress;

	jmp		JMP_B;
JMP_A:
	lea		r8, qword ptr [r12 + rax];
	mov		mapViewProc3TmpCharacterAddress, r8;
	movzx	r8d, byte ptr[r12 + rax];
	mov     edx, 3; The memory is allocated 3 byte, but the first byte is copied 3 times.
	lea     rcx, qword ptr [rbp-8];
	call	mapViewProc3CallAddress;

	; overwrite
	mov		rcx, mapViewProc3TmpCharacterAddress;
	mov		cx, word ptr [rcx+1];
	mov		word ptr [rax+1], cx; 

JMP_B:
	push	mapViewProc3ReturnAddress;
	ret;
mapViewProc3 ENDP
END