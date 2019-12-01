EXTERN	mapAdjustmentProc1ReturnAddress		:	QWORD
EXTERN	mapAdjustmentProc1CallAddress		:	QWORD
EXTERN	mapAdjustmentProc2ReturnAddress		:	QWORD
EXTERN	mapAdjustmentProc3ReturnAddress1	:	QWORD
EXTERN	mapAdjustmentProc3ReturnAddress2	:	QWORD
EXTERN	mapAdjustmentProc4ReturnAddress		:	QWORD
EXTERN	mapAdjustmentProc5ReturnAddress		:	QWORD

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
MAP_LIMIT		=	2Dh-1

.DATA
Separator	DB	"@@", 0

.CODE
mapAdjustmentProc1 PROC
	movzx	eax, byte ptr [rdi + rbx];
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
	call	mapAdjustmentProc1CallAddress;
	mov		byte ptr [rdi+rbx], al;
	jmp		JMP_C;

JMP_B:
	mov		byte ptr [rdi + rbx], 0DEh;
	jmp		JMP_C;

JMP_A:
	add		esi, 2;

JMP_C:
	inc		esi;
	mov		ebx, esi;
	cmp		byte ptr [rdi + rsi], 0;

	push	mapAdjustmentProc1ReturnAddress;
	ret;
mapAdjustmentProc1 ENDP

;-------------------------------------------;

mapAdjustmentProc2 PROC
	cmp		al, ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_4;
	jz		JMP_A;

	lea     rax, qword ptr [rbp + 220h - 218h];
	or      r8, 0FFFFFFFFFFFFFFFFh;
	nop;

JMP_B:
	inc     r8;
	cmp     byte ptr [rax+r8], 0;
	jnz		JMP_B;
	jmp		JMP_C;

JMP_A:
	mov		r8, 3;

	lea     rax, qword ptr [rbp + 220h - 1A0h];
	cmp     qword ptr [rbp + 220h - 188h], 10h;
	cmovnb  rax, qword ptr [rbp + 220h - 1A0h];
	mov		dx, word ptr [rax + rbx + 1];

	mov		word ptr[rbp + 220h - 218h + 1], dx;
	add		rbx, 2;

JMP_C:
	push	mapAdjustmentProc2ReturnAddress;
	ret;
mapAdjustmentProc2 ENDP

;-------------------------------------------;

mapAdjustmentProc3 PROC
	mov		dword ptr[rbp + 220h - 218h], 0000h;
	cmp     rbx, rdi;
	jz		JMP_A;
	or      r9, 0FFFFFFFFFFFFFFFFh;
	xor     r8d, r8d;
	lea     rdx, qword ptr [rbp + 220h - 138h];
	lea     rcx, qword ptr [rbp + 220h - 1C0h];

	push	mapAdjustmentProc3ReturnAddress1;
	ret;

JMP_A:
	push	mapAdjustmentProc3ReturnAddress2;
	ret;
mapAdjustmentProc3 ENDP

;-------------------------------------------;

mapAdjustmentProc4 PROC
	lea		rax, [rbp + 220h - 1A0h];
	cmp		r10, 10h;
	cmovnb	rax, r11;

	cmp		byte ptr[rax + rcx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rax + rcx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rax + rcx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rax + rcx], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx	eax, byte ptr[rax + rcx];
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rax + rcx + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rax + rcx + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rax + rcx + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rax + rcx + 1];
	add		eax, SHIFT_4;

JMP_F:
	add		rcx, 2;
	cmp		rcx, MAP_LIMIT;
	ja		JMP_G;

	cmp		eax, NO_FONT;
	ja		JMP_E;
JMP_G:
	mov		eax, NOT_DEF;
	movzx	eax, ax;

JMP_E:

	push	mapAdjustmentProc4ReturnAddress;
	ret;
mapAdjustmentProc4 ENDP

;-------------------------------------------;

mapAdjustmentProc5 PROC
	lea		r8,	Separator;
	lea     rdx, [rbp+190h-118h];
	lea     rcx, [rbp+190h-50h];
	push	mapAdjustmentProc5ReturnAddress;
	ret;
mapAdjustmentProc5 ENDP
END