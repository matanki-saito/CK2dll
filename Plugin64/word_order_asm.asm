EXTERN	insert						:	QWORD
EXTERN	append						:	QWORD
EXTERN	wordOrderProc1ReturnAddress	:	QWORD

EXTERN year: QWORD
EXTERN month: QWORD
EXTERN day: QWORD

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
wordOrderProc1 PROC
	nop;

	; 870年
	lea		rcx, [rbp + 0A0h - 90h];
	lea		rdx, [rbp + 0A0h - 110h];
	mov		r8, year;
	call	append;
	nop;

	; 870年1月
	lea		r8, [rbp + 0A0h - 68h];
	lea		rdx, [rsp + 180h - 110h];
	mov		rcx, rax;
	call	append;
	nop;

	; 870年1月1
	lea		r8, [rbp + 0A0h - 0F0h];
	lea		rdx, [rsp + 180h - 158h];
	mov		rcx, rax;
	call	append;
	nop;

	; 870年1月1日 
	mov		r8, day;
	lea		rdx, [rsp + 180h - 130h];
	mov		rcx, rax;
	call	append;
	nop;

	push	wordOrderProc1ReturnAddress;
	ret;
wordOrderProc1 ENDP

;----------------------;
END