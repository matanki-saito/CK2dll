EXTERN	append						:	QWORD
EXTERN	constructFromKey			:	QWORD
EXTERN	appendFromStatic			:	QWORD
EXTERN	constructFromStatic			:	QWORD
EXTERN	wordOrderProc1ReturnAddress	:	QWORD
EXTERN	wordOrderProc2ReturnAddress	:	QWORD

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

.DATA
	formatStart	DB	0A7h,059h,000h
	keyHouse	DB	"HOUSE"


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

wordOrderProc2 PROC
	nop;

	; ドートヴィル
	mov		rax, qword ptr[r15];
	lea		rdx, [rbp + 40h];
	mov		rcx, r15;
	call	qword ptr [rax + 58h];
	nop;

	; <Y>ドートヴィル
	mov     r8, rax;
	lea     rdx, formatStart;
	lea     rcx, [rbp+0];
	call	appendFromStatic;
	nop;

	; 家
	lea		rdx, keyHouse;
	lea     rcx, [rbp+20h];
	call	constructFromKey;
	nop;

	; <Y>ドートヴィル家
	mov		r8, rax;
	lea		rdx, [rbp - 40h];
	lea		rcx, [rbp+0];
	call	append;
	nop;

	; <Y>ドートヴィル家 
	lea		r8, [rsp + 2F8h - 2B8h];
	lea		rdx, [rbp - 20h];
	mov		rcx, rax;
	call	append;
	nop;
	
	; <Y>ドートヴィル家 </Y>
	lea		r8, [rsp + 2F8h - 298h];
	lea		rdx, [rbp - 60h];
	mov		rcx, rax;
	call	append;

	push	wordOrderProc2ReturnAddress;
	ret;
wordOrderProc2 ENDP

END