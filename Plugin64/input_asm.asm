EXTERN	inputProc1ReturnAddress1	:	QWORD
EXTERN	inputProc1ReturnAddress2	:	QWORD
EXTERN	inputProc1CallAddress		:	QWORD
EXTERN	inputProc2ReturnAddress		:	QWORD

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

.DATA
	inputProc1Var1	DB		03,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
	inputProc1Tmp	DQ		0
	inputProc2Tmp	DQ		0
	inputProc2Tmp2	DQ		0

.CODE
inputProc1 PROC
	; ecxにはIMEからエスケープ済みの文字が渡されてくる
	mov		ecx, dword ptr [rbp + 57h - 6Ch];

	mov		ebx, r15d;

	; JMP_X,Yについての説明。MakeJMPでコードが破壊されてしまうため、処理を丸ごとコピーしてきている。
	; ここで80hと比較しているのはUTF8でU+0000 … U+007Fかどうか確認するため
	; https://ja.wikipedia.org/wiki/UTF-8
	cmp		cl, 0FFh;
	jnb		JMP_A;
	movzx	ebx, cl;
	jmp     JMP_B;

JMP_A:
	cmp		cl, 0FFh;
	jnb		JMP_B;
	movzx	eax, byte ptr [rbp + 57h - 6Bh];
	movzx	ebx,cl;
	and		eax, 3Fh;
	and		ebx, 1Fh;
	shl		ebx, 6;
	or		ebx, eax;

JMP_B:

	push	inputProc1ReturnAddress1;
	ret;
inputProc1 ENDP

;-------------------------------------------;

; 下記はqword ptr [rax+138h];の関数（40 57 48 83 EC 20 48 8B 01 48 8B F9 48 8B 90 68 01 00 00）から割り出した
; rdi+54h : キャレット位置
; rdi+40h : 文字列長さ
; rdi+30h : 文字列アドレス

inputProc2 PROC
	mov		inputProc2Tmp2,rsi; // カウンタとして使う
	xor		rsi,rsi; 

	mov		rcx, qword ptr [rdi + 40h];
	cmp		rcx, 10h;
	lea		rcx, [rdi + 30h];
	jbe		JMP_A;
	mov		rcx, [rcx];
	
JMP_A:
	movsxd	rax, dword ptr [rdi + 54h];
	sub		rax, 3;
	js		JMP_C;
	mov		al, byte ptr [rcx + rax];
	cmp		al, ESCAPE_SEQ_1;
	jz		JMP_B;
	cmp		al, ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		al, ESCAPE_SEQ_3;
	jz		JMP_B;
	cmp		al, ESCAPE_SEQ_4;
	jnz		JMP_C;

JMP_B:
	mov		rsi, 2;

JMP_C:
	mov		rax, qword ptr [rdi];
	mov		rcx, rdi;
	test	ebx, ebx;
	jz		JMP_D;
	call	qword ptr [rax+140h];
	jmp		JMP_E;

JMP_D:
	call	qword ptr [rax+138h];

JMP_E:
	cmp		rsi, 0;
	jz      JMP_F;
	dec		rsi;
	jmp		JMP_C;

JMP_F:
	mov		rsi,inputProc2Tmp2;

	push	inputProc2ReturnAddress;
	ret;
inputProc2 ENDP
END