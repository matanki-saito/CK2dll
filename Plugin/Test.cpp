

//uintptr_t aa_retn_address_1;
//__declspec(naked) void AA()
//{
//	__asm {
//		mov esi, eax;
//		lea ecx, [ebp - 0xD4];
//		mov eax, ecx;
//
//		cmp dword ptr[eax + 0x14], 0x10;
//		jb aa_2;
//
//		mov eax, [eax];
//
//	aa_2:
//		mov al, [eax];
//
//		cmp al, 0x10;
//		jz aa_3;
//
//		cmp al, 0x11;
//		jz aa_3;
//
//		cmp al, 0x12;
//		jz aa_3;
//
//		cmp al, 0x13;
//		jz aa_3;
//
//		jmp aa_4;
//
//	aa_3:
//		push 3;
//		jmp aa_6;
//
//	aa_4:
//		push 1;
//
//	aa_6:
//		push aa_retn_address_1;
//		ret;
//	}
//};


//
//	/* */
//	uintptr_t u_4;
//	uintptr_t u_2;
//	__declspec(naked) void u_1()
//	{
//		__asm {
//			mov al, [edi + esi];
//
//			cmp al, ESCAPE_SEQ_1;
//			jz u_3;
//
//			cmp al, ESCAPE_SEQ_2;
//			jz u_3;
//
//			cmp al, ESCAPE_SEQ_3;
//			jz u_3;
//
//			cmp al, ESCAPE_SEQ_4;
//			jz u_3;
//
//			cmp al, 0xFE;
//			
//			push u_4;
//			ret;
//
//		u_3:
//			add esi, 3;
//			
//			push u_2;
//			ret;
//		}
//	}
//
//	/* */
//	uintptr_t v_4;
//	uintptr_t v_1;
//	__declspec(naked) void v_2()
//	{
//		__asm {
//			mov al, [edi + esi];
//
//			cmp al, ESCAPE_SEQ_1;
//			jz v_3;
//
//			cmp al, ESCAPE_SEQ_2;
//			jz v_3;
//
//			cmp al, ESCAPE_SEQ_3;
//			jz v_3;
//
//			cmp al, ESCAPE_SEQ_4;
//			jz v_3;
//
//			push v_4;
//			ret;
//
//		v_3:
//			add esi, 3;
//
//			push v_1;
//			ret;
//		}
//	}
//
//	uintptr_t dd_5;
//	uintptr_t dd_4;
//	__declspec(naked) void dd_1()
//	{
//		__asm {
//			cmp cl, ESCAPE_SEQ_1;
//			jz dd_3;
//
//			cmp cl, ESCAPE_SEQ_2;
//			jz dd_3;
//
//			cmp cl, ESCAPE_SEQ_3;
//			jz dd_3;
//
//			cmp cl, ESCAPE_SEQ_4;
//			jz dd_3;
//
//			cmp cl, 0x20;
//			jz dd_3;
//			jmp dd_2;
//
//		dd_3:
//			mov eax, esi;
//
//		dd_2:
//			mov[ebp - 0x1C], eax;
//			xor eax, eax;
//			
//			cmp cl, ESCAPE_SEQ_1;
//			jz dd_6;
//
//			cmp cl, ESCAPE_SEQ_2;
//			jz dd_6;
//
//			cmp cl, ESCAPE_SEQ_3;
//			jz dd_6;
//
//			cmp cl, ESCAPE_SEQ_4;
//			jz dd_6;
//			
//			cmp cl, 0x20;
//			jz dd_6;
//
//			push dd_5;
//			ret;
//
//		dd_6:
//			push dd_4;
//			ret;
//		}
//	}
//
//	uintptr_t k_2;
//	__declspec(naked) void k_1()
//	{
//		__asm {
//			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
//			jz k_10;
//
//			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
//			jz k_11;
//
//			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
//			jz k_12;
//
//			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
//			jz k_13;
//
//			mov al, [eax + esi];
//			movzx eax, al;
//			jmp k_6;
//
//		k_10:
//			movzx eax, word ptr[eax + esi + 1];
//			jmp k_1x;
//
//		k_11:
//			movzx eax, word ptr[eax + esi + 1];
//			sub eax, SHIFT_2;
//			jmp k_1x;
//
//		k_12:
//			movzx eax, word ptr[eax + esi + 1];
//			add eax, SHIFT_3;
//			jmp k_1x;
//
//		k_13:
//			movzx eax, word ptr[eax + esi + 1];
//			add eax, SHIFT_4;
//
//		k_1x:
//			add esi, 2;
//			movzx eax, ax;
//			cmp eax, NO_FONT;
//			ja k_6;
//			mov eax, NOT_DEF;
//
//		k_6:
//			mov ecx, [ebp - 0x20];
//			
//			cmp ax, 0x20;
//			jz k_2_2;
//			
//			cmp ax, 0x100;
//			ja k_2_2;
//
//			cmp word ptr[ebp - 0x8C + 2], 0x100;
//			jb k_2_5;
//
//		k_2_6:
//			mov word ptr[ebp - 0x8C + 2], 9;
//			jmp k_2_3;
//
//		k_2_5:
//			cmp word ptr[ebp - 0x8C + 2], 9;
//			jz k_2_6;
//
//		k_2_2:
//			mov word ptr[ebp - 0x8C + 2], ax;
//
//		k_2_3:
//			push k_2;
//			ret;			
//		}
//	}
//
//	uintptr_t w_2;
//	__declspec(naked) void w_1()
//	{
//		__asm {
//			cmp word ptr [ebp - 0x8C + 2], 0x100;
//			jb w_3;
//
//			sub esi, 2;
//
//		w_3:
//			mov eax, [ebp + 0x18];//arg_10
//			add eax, [ebp - 0x24];
//
//			push w_2;
//			ret;
//		}
//	}
//
//	uintptr_t ee_2;
//	uintptr_t ee_3;
//	__declspec(naked) void ee_1_1()
//	{
//		__asm {
//			cmp word ptr[ebp - 0x8C + 2], 9;
//			jz ee_2_jmp;
//			cmp word ptr[ebp - 0x8C + 2], 0x100;
//			ja ee_2_jmp;
//			cmp ebx, [ebp - 0x18];
//			jg ee_3_jmp;
//			jmp ee_2_jmp;
//		
//		ee_2_jmp:
//			push ee_2;
//			ret;
//
//		ee_3_jmp:
//			push ee_3;
//			ret;
//		}
//	}
//
//	// dummy
//	void __fastcall X_f1(void *p) {
//		__asm {
//			nop;
//			nop;
//			nop;
//			nop;
//			nop;
//			nop;
//			nop;
//		}
//	}
//
//	uintptr_t x_2;
//	__declspec(naked) void x_1()
//	{
//		__asm {
//			cmp word ptr[ebp - 0x8C + 2], 0x100;
//			jb x_4;
//
//			mov ecx, [eax + 0x10];
//			sub ecx, 1;
//			mov[eax + 0x10], ecx;
//
//		x_4:
//			lea ecx, [ebp - 0x70];
//
//			call X_f1;
//			
//			push x_2;
//			ret;
//		}
//	}
//
//	uintptr_t loc_194690F;
//	__declspec(naked) void x_5()
//	{
//		__asm {
//			cmp word ptr[ebp - 0x8C + 2], 0x100;
//			jb x_6;
//			sub esi, 1;
//		x_6:
//			mov[ebp - 0x14], 0;
//			push loc_194690F;
//			ret;
//		}
//	}
//
//	uintptr_t cc_4;
//	__declspec(naked) void cc_1()
//	{
//		__asm {
//			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
//			jz cc_10;
//
//			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
//			jz cc_11;
//
//			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
//			jz cc_12;
//
//			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
//			jz cc_13;
//
//			movzx eax, byte ptr[eax + esi];
//			jmp cc_3;
//
//		cc_10:
//			movzx eax, word ptr[eax + esi + 1];
//			jmp cc_6;
//
//		cc_11:
//			movzx eax, word ptr[eax + esi + 1];
//			sub eax, SHIFT_2;
//			jmp cc_6;
//
//		cc_12:
//			movzx eax, word ptr[eax + esi + 1];
//			add eax, SHIFT_3;
//			jmp cc_6;
//		
//		cc_13:
//			movzx eax, word ptr[eax + esi + 1];
//			add eax, SHIFT_4;
//
//		cc_6:
//			movzx eax, ax;
//			cmp eax, NO_FONT;
//			ja cc_2;
//			mov eax, NOT_DEF;
//
//		cc_2:
//			add esi, 2;
//
//		cc_3:
//			mov ecx, [esp + 0x48 - 0x28];
//
//			push cc_4;
//			ret;
//		}
//	}
//
//	uintptr_t l_5;
//	__declspec(naked) void l_1()
//	{
//		__asm {
//			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
//			jz l_10;
//
//			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
//			jz l_11;
//
//			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
//			jz l_12;
//
//			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
//			jz l_13;
//
//			jmp l_2;
//
//		l_10:
//			movzx eax, word ptr[eax + esi + 1];
//			jmp l_1x;
//		l_11:
//			movzx eax, word ptr[eax + esi + 1];
//			sub eax, SHIFT_2;
//			jmp l_1x;
//		l_12:
//			movzx eax, word ptr[eax + esi + 1];
//			add eax, SHIFT_3;
//			jmp l_1x;
//		l_13:
//			movzx eax, word ptr[eax + esi + 1];
//			add eax, SHIFT_4;
//			jmp l_1x;
//
//		l_1x:
//			add esi, 2;
//			movzx eax, ax;
//			cmp eax, NO_FONT;
//			ja l_3
//			mov eax, NOT_DEF;
//		l_3:
//			jmp l_4;
//
//		l_2:
//			movzx eax, byte ptr[eax + esi];
//		l_4:
//			mov edx, [ebp - 0x0C];
//			push l_5;
//			ret;
//		}
//	}
//
//	uintptr_t p_5;
//	__declspec(naked) void p_1()
//	{
//		__asm {
//			cmp byte ptr[eax + ebx], ESCAPE_SEQ_1;
//			jz p_10;
//
//			cmp byte ptr[eax + ebx], ESCAPE_SEQ_2;
//			jz p_11;
//
//			cmp byte ptr[eax + ebx], ESCAPE_SEQ_3;
//			jz p_12;
//
//			cmp byte ptr[eax + ebx], ESCAPE_SEQ_4;
//			jz p_13;
//
//			mov al, [eax + ebx];
//			lea ecx, [ebp - 0xFC];
//			mov byte ptr[ebp - 0x34], al;
//
//			push p_5;
//			ret;
//
//		p_10:
//			movzx eax, word ptr[eax + ebx + 1];
//			lea ecx, [ebp - 0x34];
//			mov byte ptr[ecx], ESCAPE_SEQ_1;
//			mov[ecx + 1], ax;
//			jmp p_1x;
//
//		p_11:
//			movzx eax, word ptr[eax + ebx + 1];
//			lea ecx, [ebp - 0x34];
//			mov byte ptr[ecx], ESCAPE_SEQ_2;
//			mov[ecx + 1], ax;
//			jmp p_1x;
//
//		p_12:
//			movzx eax, word ptr[eax + ebx + 1];
//			lea ecx, [ebp - 0x34];
//			mov byte ptr[ecx], ESCAPE_SEQ_3;
//			mov[ecx + 1], ax;
//			jmp p_1x;
//
//		p_13:
//			movzx eax, word ptr[eax + ebx + 1];
//			lea ecx, [ebp - 0x34];
//			mov byte ptr[ecx], ESCAPE_SEQ_4;
//			mov[ecx + 1], ax;
//
//		p_1x:
//			lea ecx, [ebp - 0xFC];
//
//			push p_5;
//			ret;
//		}
//	}
//
//	uintptr_t q_4;
//	__declspec(naked) void q_1()
//	{
//		__asm {
//			cmp byte ptr[eax], ESCAPE_SEQ_1;
//			jz q_2;
//
//			cmp byte ptr[eax], ESCAPE_SEQ_2;
//			jz q_2;
//
//			cmp byte ptr[eax], ESCAPE_SEQ_3;
//			jz q_2;
//
//			cmp byte ptr[eax], ESCAPE_SEQ_4;
//			jz q_2;
//
//			jmp q_3;
//
//		q_2:
//			mov ecx, [ebp - 0x34];
//			mov[eax], ecx;
//			mov byte ptr[eax + 0x10], 3;
//
//		q_3:
//			push 0xFFFFFFFF;
//			push 0;
//			push eax;
//
//			push q_4;
//			ret;
//		}
//	}
//
//	uintptr_t o_5;
//	__declspec(naked) void o_1()
//	{
//		__asm {
//			cmp byte ptr[eax + ebx], ESCAPE_SEQ_1;
//			jz o_10;
//
//			cmp byte ptr[eax + ebx], ESCAPE_SEQ_2;
//			jz o_11;
//
//			cmp byte ptr[eax + ebx], ESCAPE_SEQ_3;
//			jz o_12;
//
//			cmp byte ptr[eax + ebx], ESCAPE_SEQ_4;
//			jz o_13;
//
//			jmp o_3;
//
//		o_10:
//			movzx eax, word ptr[eax + ebx + 1];
//			jmp o_1x;
//
//		o_11:
//			movzx eax, word ptr[eax + ebx + 1];
//			sub eax, SHIFT_2;
//			jmp o_1x;
//
//		o_12:
//			movzx eax, word ptr[eax + ebx + 1];
//			add eax, SHIFT_3;
//			jmp o_1x;
//
//		o_13:
//			movzx eax, word ptr[eax + ebx + 1];
//			add eax, SHIFT_4;
//	
//		o_1x:
//			movzx eax, ax;
//			cmp eax, NO_FONT;
//			ja o_2;
//			mov eax, NOT_DEF;
//
//		o_2:
//			add ebx, 2;
//			jmp o_4;
//
//		o_3:
//			movzx eax, byte ptr[eax + ebx];
//
//		o_4:
//			mov edx, [ebp - 0x20];
//
//			push o_5;
//			ret;
//		}
//	}
//
//	uintptr_t n_4;
//	__declspec(naked) void n_1()
//	{
//		__asm {
//			cmp byte ptr[eax + ecx], ESCAPE_SEQ_1;
//			jz n_10;
//
//			cmp byte ptr[eax + ecx], ESCAPE_SEQ_2;
//			jz n_11;
//
//			cmp byte ptr[eax + ecx], ESCAPE_SEQ_3;
//			jz n_12;
//
//			cmp byte ptr[eax + ecx], ESCAPE_SEQ_4;
//			jz n_13;
//
//			jmp n_3;
//
//		n_10:
//			movzx eax, word ptr[eax + ecx + 1];
//			jmp n_1x;
//
//		n_11:
//			movzx eax, word ptr[eax + ecx + 1];
//			sub eax, SHIFT_2;
//			jmp n_1x;
//
//		n_12:
//			movzx eax, word ptr[eax + ecx + 1];
//			add eax, SHIFT_3;
//			jmp n_1x;
//
//		n_13:
//			movzx eax, word ptr[eax + ecx + 1];
//			add eax, SHIFT_4;
//
//		n_1x:
//			add ecx, 2;
//			movzx eax, ax;
//			mov[ebp - 0x14], ecx;
//
//			cmp eax, NO_FONT;
//			ja n_2;
//			mov eax, NOT_DEF;
//
//		n_2:
//			jmp n_5;
//
//		n_3:
//			movzx eax, byte ptr[eax + ecx];
//		n_5:
//			mov edx, [edx + eax * 4 + 0x8C];
//
//			push n_4;
//			ret;
//		}
//	}
//
//	uintptr_t j_7;
//	uintptr_t j_8;
//	__declspec(naked) void j_1()
//	{
//		__asm {
//			mov al, [esi + edx];
//
//			cmp al, ESCAPE_SEQ_1;
//			jz j_10;
//
//			cmp al, ESCAPE_SEQ_2;
//			jz j_11;
//
//			cmp al, ESCAPE_SEQ_3;
//			jz j_12;
//
//			cmp al, ESCAPE_SEQ_4;
//			jz j_13;
//
//			mov[ebp - 0x2], al;
//			movzx eax, al;
//			jmp j_6
//
//		j_10:
//			movzx eax, word ptr[esi + edx + 1];
//			jmp j_2;
//
//		j_11:
//			movzx eax, word ptr[esi + edx + 1];
//			sub eax, SHIFT_2;
//			jmp j_2;
//
//		j_12:
//			movzx eax, word ptr[esi + edx + 1];
//			add eax, SHIFT_3;
//			jmp j_2;
//
//		j_13:
//			movzx eax, word ptr[esi + edx + 1];
//			add eax, SHIFT_4;
//		
//		j_2:
//			movzx eax, ax;
//			cmp eax, NO_FONT;
//
//			ja j_3;
//			mov eax, NOT_DEF;
//
//		j_3:
//			mov[ebp - 0x2], 0x10;
//			add esi, 2;
//
//			cmp esi, ebx;
//			jnb j_4;
//
//		j_6:
//			mov ecx, [ebp - 0x10];
//			push j_7;
//			ret;
//
//		j_4:
//			mov ecx, [ebp - 0x8];
//			push j_8;
//			ret;
//		}
//	}
//

//
//	uintptr_t xx_end;
//	uintptr_t xx_end2;
//	__declspec(naked) void heap_alloc_f1() {
//		__asm {
//			nop;
//			nop;
//			nop;
//			add eax, 1;
//		}
//	}
//	__declspec(naked) void heap_free_f1() {
//		__asm {
//			nop;
//			nop;
//			nop;
//			add eax, 2;
//		}
//	}
//	__declspec(naked) void PHYSFS_utf8ToUcs2_f1() {
//		__asm {
//			nop;
//			nop;
//			nop;
//			add eax, 3;
//		}
//	}
//	__declspec(naked) void sub_122FEC0_f1() {
//		__asm {
//			nop;
//			nop;
//			nop;
//			add eax, 4;
//		}
//	}
//
//	__declspec(naked) void xx_start()
//	{
//		__asm {
//			mov ecx, [ebp - 0x64];
//
//			cmp ch, 0;
//			jnz xx_1;
//
//			xor esi, esi;
//			push xx_end;
//			ret;
//
//		xx_1:
//			push 0xFF;	/* dwBytes */
//			call heap_alloc_f1;
//			pop ecx;
//
//			test eax, eax;
//			jz xx_1;
//			
//			push 0;
//			push 0xFF;
//			lea eax, [eax];
//			mov[ebp - 0x74], eax;
//			push eax;
//			lea ecx, [ebp - 0x64];
//			push ecx;
//			call PHYSFS_utf8ToUcs2_f1;
//			add esp, 0x10;
//
//			push 0xFF; /* dwBytes */
//			call heap_alloc_f1;
//			pop ecx;
//
//			/* push */
//			push edi;
//			push ebx;
//
//			xor edi, edi;
//			mov[ebp - 0x78], eax;
//
//			xor esi, esi;
//
//		xx_2:
//			mov eax, [ebp - 0x74];
//			movzx ax, word ptr[eax + esi];
//
//			// 終了
//			cmp ax, 0;
//			jz xx_10;
//
//			// 2バイトじゃない
//			cmp ah, 0;
//			jz xx_2_1;
//
//			xor ecx, ecx;
//			mov ecx, ESCAPE_SEQ_1;
//
//			cmp ah, 0xA4;
//			jz xx_4;
//
//			cmp ah, 0xA3;
//			jz xx_4;
//
//			cmp ah, 0xA7;
//			jz xx_4;
//
//			cmp ah, 0x24;
//			jz xx_4;
//
//			cmp ah, 0x5B;
//			jz xx_4;
//
//			cmp ah, 0x0;
//			jz xx_4;
//
//			cmp ah, 0x5C;
//			jz xx_4;
//
//			cmp ah, 0x20;
//			jz xx_4;
//
//			cmp ah, 0x0D;
//			jz xx_4;
//
//			cmp ah, 0x0A;
//			jz xx_4;
//
//			cmp ah, 0x22;
//			jz xx_4;
//
//			cmp ah, 0x7B;
//			jz xx_4;
//
//			cmp ah, 0x7D;
//			jz xx_4;
//
//			cmp ah, 0x40;
//			jz xx_4;
//
//			cmp ah, 0x3B;
//			jz xx_4;
//
//			cmp ah, 0x80;
//			jz xx_4;
//
//			cmp ah, 0x7E;
//			jz xx_4;
//
//			cmp ah, 0xBD;
//			jz xx_4;
//
//			cmp ah, 0x5F;
//			jnz xx_3;
//
//		xx_4:
//			add ecx, 2;
//
//		xx_3:
//			cmp al, 0xA4;
//			jz xx_5;
//
//			cmp al, 0xA3;
//			jz xx_5;
//
//			cmp al, 0xA7;
//			jz xx_5;
//
//			cmp al, 0x24;
//			jz xx_5;
//
//			cmp al, 0x5B;
//			jz xx_5;
//
//			cmp al, 0x0;
//			jz xx_5;
//
//			cmp al, 0x5C;
//			jz xx_5;
//
//			cmp al, 0x20;
//			jz xx_5;
//
//			cmp al, 0x0D;
//			jz xx_5;
//
//			cmp al, 0x0A;
//			jz xx_5;
//
//			cmp al, 0x22;
//			jz xx_5;
//
//			cmp al, 0x7B;
//			jz xx_5;
//
//			cmp al, 0x7D;
//			jz xx_5;
//
//			cmp al, 0x40;
//			jz xx_5;
//
//			cmp al, 0x3B;
//			jz xx_5;
//
//			cmp al, 0x80;
//			jz xx_5;
//
//			cmp al, 0x7E;
//			jz xx_5;
//
//			cmp al, 0xBD;
//			jz xx_5;
//
//			cmp al, 0x5F;
//			jnz xx_6;
//
//		xx_5:
//			add ecx, 1;
//
//		xx_6:
//			cmp ecx, ESCAPE_SEQ_2;
//			jnz xx_6_1;
//			add al, LOW_SHIFT;
//			jmp xx_7;
//
//		xx_6_1:
//			cmp ecx, ESCAPE_SEQ_3;
//			jnz xx_6_2;
//			sub ah, HIGH_SHIFT;
//			jmp xx_7;
//
//		xx_6_2:
//			cmp ecx, ESCAPE_SEQ_4;
//			jnz xx_7;
//			add al, LOW_SHIFT;
//			sub ah, HIGH_SHIFT;
//		
//		xx_7:
//			add esi, 2;
//			mov ebx, [ebp - 0x78];
//			mov[ebx + edi], cl;
//			mov[ebx + edi + 1], ax;
//			add edi, 3;
//
//			jmp xx_2;
//
//		xx_2_1:
//			inc esi;
//			mov ebx, [ebp - 0x78];
//			mov byte ptr [ebx + edi], al;
//			inc edi;
//
//			jmp xx_2;
//
//		/* LOOP END */
//
//		xx_10:
//			/* pop */
//			pop ebx;
//			pop edi;
//
//			/* count */
//			xor esi, esi;
//
//		xx_12:
//			mov ecx, [ebp - 0x78];
//			movzx ecx,byte ptr [ecx + esi];
//
//			cmp cl, 0;
//			jz xx_13;
//
//			/*  edi */
//			/* eax, esi, ecx */
//
//			lea eax, [ebp - 0x1C];
//			mov[ebp - 0x1C], ecx;
//			mov edx, [edi];
//			lea ecx, [ebp - 0x38];
//			push eax;
//			mov[ebp - 0x18], 1;
//			call sub_122FEC0_f1;
//			push eax;
//			mov ecx, edi;
//			mov edx,[edi];
//			call dword ptr[edx + 0x28];
//
//			inc esi;
//			jmp xx_12;
//
//		xx_13:
//
//			push[ebp - 0x74];
//			call heap_free_f1;
//
//			push[ebp - 0x78];
//			call heap_free_f1;
//
//			pop ecx;
//			pop ecx;
//
//			push xx_end2;
//			ret;
//		}
//	}
//
//	uintptr_t loc_172DEE2;
//	__declspec(naked) void yy_1() {
//		__asm {
//			// store reg / counter
//			push esi;
//			xor esi, esi;
//
//			mov eax, [edi + 0x28]; // 文字列長さ
//			
//			lea ecx, [edi + 0x18]; // テキスト
//
//			cmp eax, 0x10;
//			jbe yy_2;
//
//			mov ecx, [ecx];
//
//		yy_2:
//			mov eax, [edi + 0x34]; // キャレット位置
//			sub eax, 3;
//			js yy_3;
//			mov al, [ecx + eax];
//
//			cmp al, ESCAPE_SEQ_1;
//			jz yy_4;
//
//			cmp al, ESCAPE_SEQ_2;
//			jz yy_4;
//
//			cmp al, ESCAPE_SEQ_3;
//			jz yy_4;
//
//			cmp al, ESCAPE_SEQ_4;
//			jnz yy_3;
//
//		yy_4:
//			mov esi, 2;
//
//		yy_3:
//			mov eax, [edi];
//			mov ecx, edi;
//
//			test bl, bl;
//			jnz yy_6;
//
//			call dword ptr[eax + 0xA0];
//			jmp yy_5;
//
//		yy_6:
//			call dword ptr[eax + 0x9C];
//
//		yy_5:
//			cmp esi, 0;
//			jz yy_7;
//
//			sub esi, 1;
//			jmp yy_3;
//
//		yy_7:
//			// restore reg / counter
//			pop esi;
//
//			pop ebx;
//
//			push loc_172DEE2;
//			ret;
//		}
//	}
//
//	uintptr_t zz_21;
//	uintptr_t loc_18AB507;
//	__declspec(naked) void zz_8() {
//		__asm {
//			add esp, 0x14;
//			test eax, eax;
//			jz loc_18AB507_jmp;
//
//			push zz_21;
//			ret;
//
//		loc_18AB507_jmp:
//			push loc_18AB507;
//			ret;
//		}
//	}
//
//	uintptr_t zz_4;
//	uintptr_t loc_18C8D09;
//	__declspec(naked) void SDL_SetTextInputRect_f1() {
//		__asm {
//			nop;
//			nop;
//			nop;
//			add eax, 5;
//		}
//	}
//	__declspec(naked) void zz_2() {
//		__asm {
//			jz zz_5;
//			
//			push zz_4;
//			ret;
//
//		zz_5:
//			sub esp, 8;
//			mov ecx, [ebp + 0x18];
//			mov edx, [ebp + 8];
//			mov[ecx + 0x38], edx;
//			mov dword ptr[ebp - 0x14], 0;
//			mov dword ptr[ebp - 0x10], 0;
//			lea eax, [ebp - 0x14];
//			push eax;
//			call SDL_SetTextInputRect_f1;
//			add esp, 0x0C;
//			
//			push loc_18C8D09;
//			ret;
//		}
//	}
//
//	uintptr_t issue_suffix_id_r;
//	uintptr_t loc_8858F2;
//	__declspec(naked) void issue_suffix_id() {
//		__asm {
//			mov edx, [ebp - 0x18];
//			mov esi, [ebp - 0x2C];
//
//			cmp ecx, 3;
//			jl issue_suffix_id_ret;
//
//			cmp edx, 0x10;
//			lea eax, [ebp - 0x2C];
//			cmovnb eax, esi;
//
//			cmp byte ptr[ecx + eax - 3], 0x10;
//			jz issue_suffix_id_fix;
//			cmp byte ptr[ecx + eax - 3], 0x11;
//			jz issue_suffix_id_fix;
//			cmp byte ptr[ecx + eax - 3], 0x12;
//			jz issue_suffix_id_fix;
//			cmp byte ptr[ecx + eax - 3], 0x13;
//			jz issue_suffix_id_fix;
//
//			jmp issue_suffix_id_ret;
//
//		issue_suffix_id_fix:
//			push loc_8858F2;
//			ret;
//
//		issue_suffix_id_ret:
//
//			push issue_suffix_id_r;
//			ret;
//		}
//	}
//
//	uintptr_t issue_14_end_1;
//	__declspec(naked) void issue_14_start_1() {
//		__asm {
//			mov     ebx, [edi + 0x9C];
//			add     ebx, 0xC;
//
//			cmp [ebx], 0x10;
//			jz issue_14_true;
//			cmp [ebx], 0x11;
//			jz issue_14_true;
//			cmp [eax], 0x12;
//			jz issue_14_true;
//			cmp [ebx], 0x13;
//			jz issue_14_true;
//
//			xor ebx, ebx;
//			jmp issue_14_x;
//
//		issue_14_true:
//			mov ebx, 1;
//
//		issue_14_x:
//			cmp ebx, 1;
//			jz issue_14_1_fix;
//
//		issue_14_1_org:
//			// Titleにspaceを追加
//			lea     eax, [ebp - 0x7C]; // joinedSrc ([space])
//			mov     byte ptr[ebp - 0x4], 0x11; // profile cnt ?
//			push    eax;
//			lea     eax, [ebp - 0xF8]; // dest
//			push    eax;
//			lea     ecx, [ebp - 0x34];  // orgSrc (title)
//			jmp issue_14_1_ret;
//
//		issue_14_1_fix:
//			// あだ名にFirstNameを追加
//			lea     eax, [ebp - 0x98]; // joinedSrc ([space])
//			mov     byte ptr[ebp - 0x4], 0x11; // profile cnt ?
//			push    eax;
//			lea     eax, [ebp - 0xF8]; // dest
//			push    eax;
//			mov     ecx, [edi + 0x9C];
//			add     ecx, 0xC;
//
//		issue_14_1_ret:
//			push issue_14_end_1;
//			ret;
//		}
//	}
//
//	uintptr_t issue_14_end_2;
//	__declspec(naked) void issue_14_start_2() {
//		__asm {
//			cmp ebx, 1;
//			jz issue_14_2_fix;
//
//		issue_14_2_org:
//			//  Title+spaceにFirstNameを追加
//			lea     ecx, [ebp - 0x98]; // joinedSrc
//			mov     byte ptr[ebp - 0x4], 0x12; // profile cnt ?
//			push    ecx;
//			lea     ecx, [ebp - 0x4C]; // dest
//			push    ecx;
//			mov     ecx, eax; // orgSrc
//			jmp issue_14_2_ret;
//
//		issue_14_2_fix:
//			// あだ名+FirstNameにスペースを追加
//			lea     ecx, [ebp - 0x7C]; // joinedSrc
//			mov     byte ptr[ebp - 0x4], 0x12; // profile cnt ?
//			push    ecx;
//			lea     ecx, [ebp - 0x4C]; // dest
//			push    ecx;
//			mov     ecx, eax; // orgSrc
//
//		issue_14_2_ret:
//			push issue_14_end_2;
//			ret;
//		}
//	}
//
//	uintptr_t issue_14_end_3;
//	__declspec(naked) void issue_14_start_3() {
//		__asm {
//			cmp ebx, 1;
//			jz issue_14_3_fix;
//
//		issue_14_3_org:
//			// Title+space+FirstNameにスペースを追加
//			lea     ecx, [ebp - 0xC8];  // joinedSrc
//			mov     byte ptr[ebp - 0x4], 0x13; // profile cnt ?
//			push    ecx;
//			lea     ecx, [ebp - 0x64]; // dest
//			push    ecx;
//			mov     ecx, eax;  // orgSrc
//			jmp issue_14_3_ret;
//
//		issue_14_3_fix:
//			// あだ名+FirstName+spaceにTitleを追加
//			lea     ecx, [ebp - 0x34];  // joinedSrc
//			mov     byte ptr[ebp - 0x4], 0x13; // profile cnt ?
//			push    ecx;
//			lea     ecx, [ebp - 0x64]; // dest
//			push    ecx;
//			mov     ecx, eax;  // orgSrc
//
//		issue_14_3_ret:
//			push issue_14_end_3;
//			ret;
//		}
//	}
//
//	uintptr_t issue_14_end_4;
//	__declspec(naked) void issue_14_start_4() {
//		__asm {
//			cmp ebx, 1;
//			jz issue_14_4_fix;
//
//		issue_14_end_4:
//			// あだ名
//			mov     esi, [ebp + 0x8]; // arg_0, dest
//			mov     byte ptr[ebp - 0x4], 0x14; // prifile cnt ?
//			mov     ecx, [edi + 0x9C];
//			add     ecx, 0xC;
//			push    ecx; // joinedSrc
//			push    esi;
//			mov     ecx, eax;  // orgSrc
//			jmp issue_14_4_ret;
//			
//		issue_14_4_fix:
//			//  あだ名+FirstName+space+Titleにスペースを追加
//			mov     esi, [ebp + 0x8]; // arg_0, dest
//			mov     byte ptr[ebp - 0x4], 0x14; // prifile cnt ?
//			lea     ecx, [ebp - 0xC8]; // joinedSrc
//			push    ecx;
//			push    esi;
//			mov     ecx, eax;  // orgSrc
//
//		issue_14_4_ret:
//			push issue_14_end_4;
//			ret;
//		}
//	}


//
//		/* sub_1943B70 */
//		byte_pattern::temp_instance().find_pattern("8A 04 16 8B 4D F0 88");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), j_1);
//			j_7 = byte_pattern::temp_instance().get_first().address(12);
//		}
//		byte_pattern::temp_instance().find_pattern("3B F9 0F 4F CF 5F 5E 8B");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			j_8 = byte_pattern::temp_instance().get_first().address();
//		}
//		/* sub_1943B70 */
//
//		/* sub_1945620 マップフォント */
//		byte_pattern::temp_instance().find_pattern("8A 04 18 8D 8D 04 FF");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), p_1);
//			p_5 = byte_pattern::temp_instance().get_first().address(12);
//
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x14), q_1);
//			q_4 = byte_pattern::temp_instance().get_first().address(0x19);
//		}
//		byte_pattern::temp_instance().find_pattern("0F B6 04 18 8B 55 E0");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), o_1);
//			o_5 = byte_pattern::temp_instance().get_first().address(7);
//		}
//		byte_pattern::temp_instance().find_pattern("0F B6 04 08 8B 94 82 8C");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), n_1);
//			n_4 = byte_pattern::temp_instance().get_first().address(11);
//		}
//		/* sub_1945620 */
//
//		/* sub_1945F30 */
//		byte_pattern::temp_instance().find_pattern("8B 55 F4 0F B6 04 30");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), l_1);
//			l_5 = byte_pattern::temp_instance().get_first().address(7);
//		}
//		/* sub_1945F30 */
//
//		/* sub_1946210 */
//		byte_pattern::temp_instance().find_pattern("0F B6 04 30 8B 4C 24");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), cc_1);
//			cc_4 = byte_pattern::temp_instance().get_first().address(8);
//		}
//		/* sub_1946210 */
//
//		/* sub_19465B0　？ */
//		//スタック修正
//		byte_pattern::temp_instance().find_pattern("83 EC 7C 53 8B 5D 0C 56 57");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x7E, true);
//		}
//		byte_pattern::temp_instance().find_pattern("80 F9 20 0F 44 C6 89 45");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), dd_1);
//			dd_5 = byte_pattern::temp_instance().get_first().address(14);
//			dd_4 = byte_pattern::temp_instance().get_first().address(0x12);
//		}
//		byte_pattern::temp_instance().find_pattern("8A 04 30 8B 4D");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), k_1);
//			k_2 = byte_pattern::temp_instance().get_first().address(9);
//		}
//		byte_pattern::temp_instance().find_pattern("8B 45 18 03 45 DC 89 55");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), w_1);
//			w_2 = byte_pattern::temp_instance().get_first().address(6);
//		}
//		byte_pattern::temp_instance().find_pattern("3B 5D E8 0F 8F");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), ee_1_1);
//			ee_2 = byte_pattern::temp_instance().get_first().address(9);
//		}
//		byte_pattern::temp_instance().find_pattern("53 FF 75 E8 8D 45 90 C7");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			ee_3 = byte_pattern::temp_instance().get_first().address();
//		}
//		byte_pattern::temp_instance().find_pattern("8B 5D 0C 8B CB 6A FF 6A 00 50 C6 45 FC 02 E8");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x13), x_1);
//			x_2 = byte_pattern::temp_instance().get_first().address(0x1B);
//		}
//		byte_pattern::temp_instance().find_pattern("56 8B F1 8B 46 14 83 F8 10 72 0E");
//		if (byte_pattern::temp_instance().has_size(2)) {
//			injector::MakeJMP(X_f1, byte_pattern::temp_instance().get_first().address(0));
//		}
//		byte_pattern::temp_instance().find_pattern("8A 55 20 89 4D E4 89 75 E8");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x9), x_5);
//		}
//		byte_pattern::temp_instance().find_pattern("3B 45 14 0F 8F 70 01 00 00");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			loc_194690F = byte_pattern::temp_instance().get_first().address();
//		}
//		/* sub_19465B0　？ */
//
//		/* start sub_19BEAF0  */
//		byte_pattern::temp_instance().find_pattern("83 FB 01 72 34 56 33 F6");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x15), u_1);
//			u_4 = byte_pattern::temp_instance().get_first().address(0x1A);
//		}
//		byte_pattern::temp_instance().find_pattern("80 3C 37 00 75 D9 5E 5F");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			u_2 = byte_pattern::temp_instance().get_first().address();
//		}
//		/* end sub_19BEB40  */
//
//		/* start sub_19BEB40 */
//		byte_pattern::temp_instance().find_pattern("33 F6 80 3F 00 74 28 83 FE 01");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0xC), v_2);
//			v_4 = byte_pattern::temp_instance().get_first().address(0x11);
//		}
//		byte_pattern::temp_instance().find_pattern("80 3C 37 00 75 D8 5F 5E");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			v_1 = byte_pattern::temp_instance().get_first().address();
//		}
//		/* end sub_19BEB40 */
//

//
//		/* 日付 */
//		byte_pattern::temp_instance().find_pattern("64 20 77 20 6D 77 20 2C");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0), 0x79, true);
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(1), 0x20, true);
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x10, true);
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x74, true);
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(4), 0x5E, true);
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(5), 0x20, true);
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(6), 0x6D, true);
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(7), 0x77, true);
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(8), 0x20, true);
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(9), 0x64, true);
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(10), 0x20, true);
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(11), 0x10, true);
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(12), 0xE5, true);
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(13), 0x65, true);
//		}
//		/* 日付 */
//		
//		/* sub_15AB8F0 入力 */
//		byte_pattern::temp_instance().find_pattern("55 8B EC 83 EC 70 53 56 57 8B F9 8B DA");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(5), 0x78, true);
//		}
//		byte_pattern::temp_instance().find_pattern("8A 4D 9C 33 F6 80 F9 80");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), xx_start);
//			xx_end = byte_pattern::temp_instance().get_first().address(5);
//		}
//		byte_pattern::temp_instance().find_pattern("FF 75 A0 E8 ? ? ? ? 83 C4 04 25");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			xx_end2 = byte_pattern::temp_instance().get_first().address();
//		}
//		// same as sub_16FEEFB
//		byte_pattern::temp_instance().find_pattern("8B FF 55 8B EC 56 8B 75 08 83 FE E0");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(heap_alloc_f1, byte_pattern::temp_instance().get_first().address());
//		}
//		byte_pattern::temp_instance().find_pattern("8B FF 55 8B EC 83 7D 08 00 74 2D FF 75");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(heap_free_f1, byte_pattern::temp_instance().get_first().address());
//		}
//		// PHYSFS_utf8ToUcs2
//		byte_pattern::temp_instance().find_pattern("55 8B EC 51 8B 4D 10 53");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(PHYSFS_utf8ToUcs2_f1, byte_pattern::temp_instance().get_first().address());
//		}
//		// struct init
//		byte_pattern::temp_instance().find_pattern("C7 41 08 01 00 00 00 C7 41 0C 00 00 00 00");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(sub_122FEC0_f1, byte_pattern::temp_instance().get_first().address(-0x12));
//		}
//		/* sub_15AB8F0 入力 */
//
//		/*  Backspace */
//		byte_pattern::temp_instance().find_pattern("8B 07 84 DB 5B 8B CF");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), yy_1);
//		}
//		byte_pattern::temp_instance().find_pattern("0F B7 47 36 8B CF 50 8D 45 DC 50");
//		if (byte_pattern::temp_instance().has_size(2)) { // select first !
//			loc_172DEE2 = byte_pattern::temp_instance().get_first().address();
//		}
//		/*  Backspace */
//
//		/* show candidate and composition window */
//		// see https://twitter.com/matanki_saito/status/1005093384946479104
//		//
//		// (SDL_windowskeyboard.c)
//		//
//		// skip
//		//if (*lParam & GCS_RESULTSTR) {
//		//    IME_GetCompositionString(videodata, himc, GCS_RESULTSTR);
//		//    IME_SendInputEvent(videodata);
//		//}
//		byte_pattern::temp_instance().find_pattern("B9 00 08 00 00 8B 45");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(
//				byte_pattern::temp_instance().get_first().address(0x8),
//				byte_pattern::temp_instance().get_first().address(0x37)
//			);
//		}
//		// remove
//		// *lParam = 0;
//		byte_pattern::temp_instance().find_pattern("8B 45 14 89 08 E9 83 00");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeNOP(
//				byte_pattern::temp_instance().get_first().address(),
//				5,
//				true
//			);
//		}
//		// skip
//		//if (!videodata->ime_initialized || !videodata->ime_available || !videodata->ime_enabled)
//		//    return SDL_FALSE;
//		byte_pattern::temp_instance().find_pattern("39 4E 28 0F 84 19 02");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(
//				byte_pattern::temp_instance().get_first().address(0),
//				byte_pattern::temp_instance().get_first().address(0x1B)
//			);
//		}
//		// insert 
//		//videodata->ime_hwnd_current = hwnd;
//		//rect.x = 0;
//		//rect.y = 0;
//		//SDL_SetTextInputRect(&rect);
//		byte_pattern::temp_instance().find_pattern("0F 84 FD 00 00 00 83 E8 01");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), zz_2);
//			zz_4 = byte_pattern::temp_instance().get_first().address(0x06);
//		}
//		byte_pattern::temp_instance().find_pattern("33 DB 43 E9 E5");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			loc_18C8D09 = byte_pattern::temp_instance().get_first().address();
//		}
//		byte_pattern::temp_instance().find_pattern("55 8B EC A1 ? ? ? ? 85 C0 74 12 8B");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(SDL_SetTextInputRect_f1, byte_pattern::temp_instance().get_first().address());
//		}
//
//		// SDL_keyborad.c
//		// skip
//		// issue-9
//		//byte_pattern::temp_instance().find_pattern("85 F6 74 30 57 57 6A 0C");
//		//if (byte_pattern::temp_instance().has_size(1)) {
//		//	injector::MakeJMP(
//		//		byte_pattern::temp_instance().get_first().address(-0x6),
//		//		byte_pattern::temp_instance().get_first().address(0)
//		//	);
//		//}
//
//		// SDL_windowevent.c
//		// insert goto
//		//if (IME_HandleMessage(hwnd, msg, wParam, &lParam, data->videodata)) {
//		//	goto A;
//		//}
//		byte_pattern::temp_instance().find_pattern("83 C4 14 85 C0 74 07 33");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), zz_8);
//		}
//		byte_pattern::temp_instance().find_pattern("FF 75 14 FF 75 10 FF 75 0C FF 75 08 E9 B0 0D 00");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			zz_21 = byte_pattern::temp_instance().get_first().address();
//		}
//		byte_pattern::temp_instance().find_pattern("8B 45 0C B9 01 01 00 00");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			loc_18AB507 = byte_pattern::temp_instance().get_first().address();
//		}
//		/* Candidate */
//
//		/* dynastyに-idがついてしまう問題 */
//		byte_pattern::temp_instance().find_pattern("8B 55 E8 8B 75 D4 83 F9");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_suffix_id);
//			issue_suffix_id_r = byte_pattern::temp_instance().get_first().address(0x06);
//		}
//		byte_pattern::temp_instance().find_pattern("8B 75 C0 8D 45 D4 50 8B");
//		if (byte_pattern::temp_instance().has_size(2)) {
//			loc_8858F2 = byte_pattern::temp_instance().get_first().address();
//		}
//
//		/* File容量の制限解除 */
//		byte_pattern::temp_instance().find_pattern("81 FE 00 00 00 02");
//		if (byte_pattern::temp_instance().has_size(2)) {
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x5), 0x04, true);
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x5), 0x04, true);
//		}
//		byte_pattern::temp_instance().find_pattern("68 00 00 00 02 C7 87 8C");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x4), 0x04, true);
//		}
//
//		/* [Title] [FirstName] [NickName]となるのを[NickName] [FirstName] [Title] にする issue-14 */
//		byte_pattern::temp_instance().find_pattern("8D 45 84 C6 45 FC 11 50 8D 85 08");
//		if (byte_pattern::temp_instance().has_size(1)) {
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_14_start_1);
//			issue_14_end_1 = byte_pattern::temp_instance().get_first().address(0x12);
//
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x17), issue_14_start_2);
//			issue_14_end_2 = byte_pattern::temp_instance().get_first().address(0x28);
//
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x2D), issue_14_start_3);
//			issue_14_end_3 = byte_pattern::temp_instance().get_first().address(0x3E);
//
//			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x43), issue_14_start_4);
//			issue_14_end_4 = byte_pattern::temp_instance().get_first().address(0x57);
//		}
//	}
//}
