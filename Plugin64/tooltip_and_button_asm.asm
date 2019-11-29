EXTERN	tooltipAndButtonProc1ReturnAddress	:	QWORD
EXTERN	tooltipAndButtonProc1CallAddress	:	QWORD
EXTERN	tooltipAndButtonProc2ReturnAddress	:	QWORD
EXTERN	tooltipAndButtonProc3ReturnAddress	:	QWORD
EXTERN	tooltipAndButtonProc4ReturnAddress1	:	QWORD
EXTERN	tooltipAndButtonProc4ReturnAddress2	:	QWORD
EXTERN	tooltipAndButtonProc5ReturnAddress1	:	QWORD
EXTERN	tooltipAndButtonProc5ReturnAddress2	:	QWORD
EXTERN	tooltipAndButtonProcTestReturnAddress1	:	QWORD
EXTERN	tooltipAndButtonProcTestReturnAddress2	:	QWORD

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

; temporary space for code point
.DATA
	tooltipAndButtonProc2TmpCharacter			DD	0
	tooltipAndButtonProc2TmpCharacterAddress	DQ	0
	tooltipAndButtonProc2TmpFlag				DD	0

.CODE
tooltipAndButtonProc1 PROC
	mov     qword ptr [rbp + 440h - 3B8h], 0h;

	cmp		byte ptr [r14 + rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [r14 + rax], ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		byte ptr [r14 + rax], ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		byte ptr [r14 + rax], ESCAPE_SEQ_4;
	jz		JMP_A;

	movzx	r8d, byte ptr[r14 + rax];
	mov     rdx, 1;
	lea     rcx, qword ptr [rbp + 440h - 3B8h];
	mov		tooltipAndButtonProc2TmpFlag, 0h;
	call	tooltipAndButtonProc1CallAddress;

	jmp		JMP_B;
JMP_A:
	mov		tooltipAndButtonProc2TmpFlag, 1h;
	lea		r8, qword ptr [r14 + rax];
	mov		tooltipAndButtonProc2TmpCharacterAddress, r8;
	movzx	r8d, byte ptr[r14 + rax];
	mov     rdx, 3; The memory is allocated 3 byte, but the first byte is copied 3 times.
	lea     rcx, qword ptr [rbp + 440h - 3B8h];
	call	tooltipAndButtonProc1CallAddress;

	; overwrite
	mov		rcx, tooltipAndButtonProc2TmpCharacterAddress;
	mov		cx, word ptr [rcx+1];
	mov		word ptr [rax+1], cx;
JMP_B:
	push	tooltipAndButtonProc1ReturnAddress;
	ret;
tooltipAndButtonProc1 ENDP

;-------------------------------------------;

tooltipAndButtonProc2 PROC
	cmp		byte ptr[r14+rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[r14+rax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[r14+rax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[r14+rax], ESCAPE_SEQ_4;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[r14 + rax + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[r14 + rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[r14 + rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[r14 + rax + 1];
	add		eax, SHIFT_4;
	jmp		JMP_F;

JMP_E:
	movzx   eax, byte ptr [r14 + rax];
	jmp		JMP_G;

JMP_F:
	movzx	eax, ax;

	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	mov		r9, qword ptr [r15 + rax * 8 + 0E8h];
	mov		qword ptr [rbp + 440h - 360h], r9;

	mov		tooltipAndButtonProc2TmpCharacter, eax;

	push	tooltipAndButtonProc2ReturnAddress;
	ret;
tooltipAndButtonProc2 ENDP

;-------------------------------------------;

tooltipAndButtonProc3 PROC
	mov		ecx, ebx;
	

	cmp		byte ptr[rax + rcx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rax + rcx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rax + rcx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rax + rcx], ESCAPE_SEQ_4;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rcx + rax + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rcx + rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rcx + rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rcx + rax + 1];
	add		eax, SHIFT_4;
	jmp		JMP_F;

JMP_E:
	movzx	eax, byte ptr [rcx + rax];
	jmp		JMP_G;

JMP_F:
	movzx	eax, ax;
	add		ebx, 2;
	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	mov		r11, qword ptr [r15 + rax * 8 + 0E8h];

	push	tooltipAndButtonProc3ReturnAddress;
	ret;
tooltipAndButtonProc3 ENDP

;-------------------------------------------;

tooltipAndButtonProc4 PROC
	cmp		dword ptr [rbp + 440h -400h], 0;
	jz		JMP_A;

	cmp		tooltipAndButtonProc2TmpCharacter, 00FFh;
	ja		JMP_A;

	push	tooltipAndButtonProc4ReturnAddress1;
	ret;

JMP_A:
	cmp     dword ptr [rbp + 440h - 3E8h], 0;
	push	tooltipAndButtonProc4ReturnAddress2;
	ret;
tooltipAndButtonProc4 ENDP

;-------------------------------------------;

tooltipAndButtonProc5 PROC
	lea     rcx, qword ptr [r12 + 100h];

	cmp		byte ptr [rbx + r14], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rbx + r14], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [rbx + r14], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [rbx + r14], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx   edx, byte ptr [rbx + r14];
	jmp		JMP_G;

JMP_A:
	movzx	edx, word ptr[rbx + r14 + 1];
	jmp		JMP_F;

JMP_B:
	movzx	edx, word ptr[rbx + r14 + 1];
	sub		edx, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	edx, word ptr[rbx + r14 + 1];
	add		edx, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	edx, word ptr[rbx + r14 + 1];
	add		edx, SHIFT_4;

JMP_F:
	movzx	edx, dx;
	cmp		edx, NO_FONT;
	ja		JMP_H;
	mov		edx, NOT_DEF;

JMP_H:
	add		rbx, 3;
	add		edi, 3;
	cmp		rbx, r13;
	ja		JMP_J;
	dec		rbx;
	dec		edi;

JMP_G:
	mov     rsi, qword ptr [rcx + rdx * 8];
	test    rsi, rsi;

	push	tooltipAndButtonProc5ReturnAddress1;
	ret;

JMP_J:
	push	tooltipAndButtonProc5ReturnAddress2;
	ret;
tooltipAndButtonProc5 ENDP

tooltipAndButtonProcTest PROC
	cmp		tooltipAndButtonProc2TmpFlag, 1;
	jnz		JMP_A;

	add		ebx,2;

JMP_A:
	inc		ebx;
	cmp     ebx, dword ptr [rbp + 440h - 438h];
	jge		JMP_B;
	mov		r9d, 1;
	push	tooltipAndButtonProcTestReturnAddress1;
	ret;

JMP_B:
	push	tooltipAndButtonProcTestReturnAddress2;
	ret;
tooltipAndButtonProcTest ENDP

END