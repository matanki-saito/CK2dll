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


//

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

