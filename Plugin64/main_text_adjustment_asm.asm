EXTERN mainTextAdjustmentProc1ReturnAddress: QWORD
EXTERN mainTextAdjustmentProc2ReturnAddress1: QWORD
EXTERN mainTextAdjustmentProc2ReturnAddress2: QWORD
EXTERN mainTextAdjustmentProc3ReturnAddress: QWORD
EXTERN mainTextAdjustmentProc4ReturnAddress1: QWORD
EXTERN mainTextAdjustmentProc4ReturnAddress2: QWORD
EXTERN mainTextAdjustmentProc5ReturnAddress: QWORD
EXTERN mainTextAdjustmentProc5CallAddress: QWORD
EXTERN mainTextAdjustmentProc6ReturnAddress: QWORD

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

	cmp		eax, 20h;
	jz		k_2_2;

	cmp		eax, 100h;
	ja		k_2_2;

	cmp		dword ptr [mainTextAdjustmentProc1TmpCharacter], 100h;
	jb		k_2_5;

k_2_6:
	mov		dword ptr[mainTextAdjustmentProc1TmpCharacter], 9;
	jmp		k_2_3;

k_2_5:
	cmp		dword ptr[mainTextAdjustmentProc1TmpCharacter], 9;
	jz		k_2_6;

k_2_2:
	mov		dword ptr[mainTextAdjustmentProc1TmpCharacter], eax;

k_2_3:

	mov		r15, qword ptr [r11 + rax * 8 + 0E8h];
	test    r15, r15;
	push	mainTextAdjustmentProc1ReturnAddress;
	ret;
mainTextAdjustmentProc1 ENDP

;-------------------------------------------;

mainTextAdjustmentProc1v3332 PROC
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

	cmp		eax, 20h;
	jz		k_2_2;

	cmp		eax, 100h;
	ja		k_2_2;

	cmp		dword ptr [mainTextAdjustmentProc1TmpCharacter], 100h;
	jb		k_2_5;

k_2_6:
	mov		dword ptr[mainTextAdjustmentProc1TmpCharacter], 9;
	jmp		k_2_3;

k_2_5:
	cmp		dword ptr[mainTextAdjustmentProc1TmpCharacter], 9;
	jz		k_2_6;

k_2_2:
	mov		dword ptr[mainTextAdjustmentProc1TmpCharacter], eax;

k_2_3:

	mov		rdi, qword ptr [rdi + rax * 8 + 0E8h];
	test    rdi, rdi;
	push	mainTextAdjustmentProc1ReturnAddress;
	ret;
mainTextAdjustmentProc1v3332 ENDP

;-------------------------------------------;

mainTextAdjustmentProc2 PROC
	cmp		mainTextAdjustmentProc1TmpCharacter,100h;
	jb		JMP_A;
	add		edi,2;

JMP_A:
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

;-------------------------------------------;

mainTextAdjustmentProc2v3332 PROC
	cmp		mainTextAdjustmentProc1TmpCharacter,100h;
	jb		JMP_A;
	add		esi,2;

JMP_A:
	inc		esi;
	mov		r9, qword ptr [rbx+10h];
	cmp		esi, r9d;
	jge		JMP_B;
	mov		r10d, dword ptr [rbp + 3Fh + 38h];

	push	mainTextAdjustmentProc2ReturnAddress1;
	ret;

JMP_B:
	push	mainTextAdjustmentProc2ReturnAddress2;
	ret;
mainTextAdjustmentProc2v3332 ENDP

;-------------------------------------------;

mainTextAdjustmentProc3 PROC

	cmp		cl, ESCAPE_SEQ_1;
	jz		JMP_A;

	cmp		cl, ESCAPE_SEQ_2;
	jz		JMP_A;

	cmp		cl, ESCAPE_SEQ_3;
	jz		JMP_A;

	cmp		cl, ESCAPE_SEQ_4;
	jz		JMP_A;

	cmp		cl, 20h;

JMP_A:
	cmovz	r15d, edi;

JMP_B:
	mov		dword ptr [rbp + 3Fh + 18h], r15d;
	mov		eax, r14d;

	cmp		cl, ESCAPE_SEQ_1;
	jz		JMP_C;

	cmp		cl, ESCAPE_SEQ_2;
	jz		JMP_C;

	cmp		cl, ESCAPE_SEQ_3;
	jz		JMP_C;

	cmp		cl, ESCAPE_SEQ_4;
	jz		JMP_C;

	cmp		cl, 20h;

JMP_C:
	cmovnz	eax, r13d;

JMP_D:
	
	mov		r13d, eax;
	push	mainTextAdjustmentProc3ReturnAddress;
	ret;
mainTextAdjustmentProc3 ENDP

;-------------------------------------------;

mainTextAdjustmentProc3v3332 PROC

	cmp		cl, ESCAPE_SEQ_1;
	jz		JMP_A;

	cmp		cl, ESCAPE_SEQ_2;
	jz		JMP_A;

	cmp		cl, ESCAPE_SEQ_3;
	jz		JMP_A;

	cmp		cl, ESCAPE_SEQ_4;
	jz		JMP_A;

	cmp		cl, 20h;

JMP_A:
	cmovz	r11d, esi;

JMP_B:
	mov		dword ptr [rbp + 3Fh + 18h], r11d;
	mov		eax, r15d;

	cmp		cl, ESCAPE_SEQ_1;
	jz		JMP_C;

	cmp		cl, ESCAPE_SEQ_2;
	jz		JMP_C;

	cmp		cl, ESCAPE_SEQ_3;
	jz		JMP_C;

	cmp		cl, ESCAPE_SEQ_4;
	jz		JMP_C;

	cmp		cl, 20h;

JMP_C:
	cmovnz	eax, r13d;

JMP_D:
	
	mov		r13d, eax;
	push	mainTextAdjustmentProc3ReturnAddress;
	ret;
mainTextAdjustmentProc3v3332 ENDP

;-------------------------------------------;

mainTextAdjustmentProc4 PROC
	mov		r13d, dword ptr[ rbp + 3Fh + 28h];

	cmp		dword ptr[mainTextAdjustmentProc1TmpCharacter], 9;
	jz		JMP_B;

	cmp		dword ptr[mainTextAdjustmentProc1TmpCharacter], 100h;
	ja		JMP_B;

	; ここから下は移植
JMP_C:
	cmp		r15d, r13d;
	jle		JMP_B;
	cmp		r10d, dword ptr [rbp + 3Fh + 30h];
	jle		JMP_A;
	cmp		byte ptr [rbp + 3Fh + 50h], 0;
	jnz		JMP_B;

JMP_A: ;　左
	push	mainTextAdjustmentProc4ReturnAddress1;
	ret;

JMP_B: ; 右
	push	mainTextAdjustmentProc4ReturnAddress2;
	ret;
mainTextAdjustmentProc4 ENDP

;-------------------------------------------;

mainTextAdjustmentProc5 PROC

	;cmp		dword ptr [mainTextAdjustmentProc1TmpCharacter], 100h;
	;jb		JMP_A;

	; 文字数を1減らす
	mov		ecx, dword ptr [rax + 10h];
	dec		ecx;
	mov		dword ptr [rax + 10h], ecx;

JMP_A:
	inc		r8;
	mov     rdx, qword ptr [rsp + 0A8h - 88h];
	lea     rcx, [rsp + 0A8h - 88h];
	call	mainTextAdjustmentProc5CallAddress;

	push	mainTextAdjustmentProc5ReturnAddress;
	ret;
mainTextAdjustmentProc5 ENDP

;-------------------------------------------;

mainTextAdjustmentProc6 PROC
	mov		r15d, edi;
	mov		ecx, edi;
	mov		dword ptr [rbp + 3Fh + 28h], ecx;

	cmp		dword ptr [mainTextAdjustmentProc1TmpCharacter], 100h;
	jae		JMP_A;
	mov		r12d, r14d; // r14dが0. これをキャンセルする

JMP_A:
	mov		r10d, dword ptr [rbp + 3Fh + 38h];
	movzx	eax, byte ptr [rbp + 3Fh + 48h];

	push	mainTextAdjustmentProc6ReturnAddress;
	ret;
mainTextAdjustmentProc6 ENDP

END