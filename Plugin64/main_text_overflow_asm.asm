EXTERN	mainTextOverflowProc1ReturnAddress	:	QWORD
EXTERN	mainTextOverflowProc2ReturnAddress1	:	QWORD
EXTERN	mainTextOverflowProc2ReturnAddress2	:	QWORD
EXTERN	mainTextOverflowProc3ReturnAddress1	:	QWORD
EXTERN	mainTextOverflowProc3ReturnAddress2	:	QWORD

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

.DATA
	multibyteFlag	DD	0

.CODE
mainTextOverflowProc1 PROC
	mov		multibyteFlag, 0h;

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
	mov		multibyteFlag, 1h;
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_E;
	mov		eax, NOT_DEF;

JMP_E:
	mov		r10, qword ptr [r13 + rax * 8 +0E8h];

	test	r10,r10;
	push	mainTextOverflowProc1ReturnAddress;
	ret;
mainTextOverflowProc1 ENDP

;------------------;

mainTextOverflowProc2 PROC
	mov		edx, dword ptr [rbx + 10h];

	cmp		multibyteFlag, 0;
	jz		JMP_A;
	add		edi,2;

JMP_A:
	inc		edi;
	cmp		edi, edx;
	jge		JMP_B;

	mov		r8d, dword ptr [rsp + 78h + 20h];
	mov		r11d, dword ptr [rsp + 78h + 28h];

	push	mainTextOverflowProc2ReturnAddress2;
	ret;

JMP_B:
	push	mainTextOverflowProc2ReturnAddress1;
	ret;

mainTextOverflowProc2 ENDP

;------------------;

mainTextOverflowProc3 PROC
	lea		eax, [rdi - 3];
	mov		byte ptr [rax + rdx], 20h;
	cmp		qword ptr [r15 + 18h], 10h;
	jb		JMP_A;
	mov		rdx, [r15];

	push	mainTextOverflowProc3ReturnAddress2;
	ret;

JMP_A:
	push	mainTextOverflowProc3ReturnAddress1;
	ret;

mainTextOverflowProc3 ENDP
END