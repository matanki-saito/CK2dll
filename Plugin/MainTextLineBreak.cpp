#include "stdinc.h"
#include "byte_pattern.h"

namespace MainTextLineBreak {

	/*-----------------------------------------------*/

	uintptr_t func1_v28;
	uintptr_t func1_v30;
	uintptr_t func1_v301;
	
	/*-----------------------------------------------*/

	errno_t func_hook(RunOptions *options) {
		std::string desc = "func hook";

		switch (options->version) {
		case v2_8_X:
			// push esi
			byte_pattern::temp_instance().find_pattern("56 8B F1 8B 46 14 83 F8 10 72 0E");
			if (byte_pattern::temp_instance().has_size(2, desc)) {
				func1_v28 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;
			return NOERROR;
		case v3_0_0:
			// push esi
			byte_pattern::temp_instance().find_pattern("56 8B F1 8B 46 14 83 F8 10 72 0E");
			if (byte_pattern::temp_instance().has_size(3, desc)) {
				func1_v30 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;
			return NOERROR;
		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
			// push esi
			byte_pattern::temp_instance().find_pattern("56 8B F1 8B 46 14 83 F8 10 72 0E");
			if (byte_pattern::temp_instance().has_size(5, desc)) {
				func1_v301 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t dd_5;
	uintptr_t dd_4;
	__declspec(naked) void dd_1_v28()
	{
		__asm {
			cmp cl, ESCAPE_SEQ_1;
			jz dd_3;

			cmp cl, ESCAPE_SEQ_2;
			jz dd_3;

			cmp cl, ESCAPE_SEQ_3;
			jz dd_3;

			cmp cl, ESCAPE_SEQ_4;
			jz dd_3;

			cmp cl, 0x20;
			jz dd_3;
			jmp dd_2;

		dd_3:
			mov eax, esi;

		dd_2:
			mov [ebp - 0x1C], eax;
			xor eax, eax;
			
			cmp cl, ESCAPE_SEQ_1;
			jz dd_6;

			cmp cl, ESCAPE_SEQ_2;
			jz dd_6;

			cmp cl, ESCAPE_SEQ_3;
			jz dd_6;

			cmp cl, ESCAPE_SEQ_4;
			jz dd_6;
			
			cmp cl, 0x20;
			jz dd_6;

			push dd_5;
			ret;

		dd_6:
			push dd_4;
			ret;
		}
	}

	__declspec(naked) void dd_1_v30()
	{
		__asm {
			cmp cl, ESCAPE_SEQ_1;
			jz dd_3;

			cmp cl, ESCAPE_SEQ_2;
			jz dd_3;

			cmp cl, ESCAPE_SEQ_3;
			jz dd_3;

			cmp cl, ESCAPE_SEQ_4;
			jz dd_3;

			cmp cl, 0x20;
			jz dd_3;
			jmp dd_2;

		dd_3:
			mov eax, esi;

		dd_2:
			mov dword ptr [ebp - 0x18], eax; // ここの値だけ違う
			xor eax, eax;

			cmp cl, ESCAPE_SEQ_1;
			jz dd_6;

			cmp cl, ESCAPE_SEQ_2;
			jz dd_6;

			cmp cl, ESCAPE_SEQ_3;
			jz dd_6;

			cmp cl, ESCAPE_SEQ_4;
			jz dd_6;

			cmp cl, 0x20;
			jz dd_6;

			push dd_5;
			ret;

		dd_6:
			push dd_4;
			ret;
		}
	}

	__declspec(naked) void dd_1_v301()
	{
		__asm {
			cmp cl, ESCAPE_SEQ_1;
			jz dd_3;

			cmp cl, ESCAPE_SEQ_2;
			jz dd_3;

			cmp cl, ESCAPE_SEQ_3;
			jz dd_3;

			cmp cl, ESCAPE_SEQ_4;
			jz dd_3;

			cmp cl, 0x20;
			jz dd_3;
			jmp dd_2;

		dd_3:
			mov eax, esi;

		dd_2:
			mov dword ptr[ebp - 0x1C], eax; // ここの値だけ違う
			xor eax, eax;

			cmp cl, ESCAPE_SEQ_1;
			jz dd_6;

			cmp cl, ESCAPE_SEQ_2;
			jz dd_6;

			cmp cl, ESCAPE_SEQ_3;
			jz dd_6;

			cmp cl, ESCAPE_SEQ_4;
			jz dd_6;

			cmp cl, 0x20;
			jz dd_6;

			push dd_5;
			ret;

		dd_6:
			push dd_4;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fixA_hook(RunOptions *options) {
		std::string desc = "fixA";

		switch (options->version) {
		case v2_8_X:
			// cmp cl,20h
			byte_pattern::temp_instance().find_pattern("80 F9 20 0F 44 C6 89 45");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), dd_1_v28);
				// cmovnz eax,[ebp+var_10]
				dd_5 = byte_pattern::temp_instance().get_first().address(14);
				// mov [ebp+var_10],eax
				dd_4 = byte_pattern::temp_instance().get_first().address(0x12);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_0:
			// cmp cl,20h
			byte_pattern::temp_instance().find_pattern("80 F9 20 0F 44 C6 89 45");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), dd_1_v30);
				// cmovnz eax,[ebp+var_10]
				dd_5 = byte_pattern::temp_instance().get_first().address(14);
				// mov [ebp+var_10],eax
				dd_4 = byte_pattern::temp_instance().get_first().address(0x12);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
			// cmp cl,20h
			byte_pattern::temp_instance().find_pattern("80 F9 20 0F 44 C6 89 45");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), dd_1_v301);
				// cmovnz eax,[ebp+var_10]
				dd_5 = byte_pattern::temp_instance().get_first().address(14);
				// mov [ebp+var_10],eax
				dd_4 = byte_pattern::temp_instance().get_first().address(0x12);
			}
			else return CK2ERROR1;
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t k_2;
	__declspec(naked) void k_1()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz k_10;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz k_11;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz k_12;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz k_13;

			mov al, [eax + esi];
			movzx eax, al;
			jmp k_6;

		k_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp k_1x;

		k_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp k_1x;

		k_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp k_1x;

		k_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;

		k_1x:
			add esi, 2;
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja k_6;
			mov eax, NOT_DEF;

		k_6:
			mov ecx, [ebp - 0x20];

			cmp ax, 0x20;
			jz k_2_2;

			cmp ax, 0x100;
			ja k_2_2;

			cmp word ptr[ebp - 0x8C + 2], 0x100;
			jb k_2_5;

		k_2_6:
			mov word ptr[ebp - 0x8C + 2], 9;
			jmp k_2_3;

		k_2_5:
			cmp word ptr[ebp - 0x8C + 2], 9;
			jz k_2_6;

		k_2_2:
			mov word ptr[ebp - 0x8C + 2], ax;

		k_2_3:
			push k_2;
			ret;
		}
	}

	uintptr_t k_2_v310;
	__declspec(naked) void k_1_v310()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz k_10;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz k_11;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz k_12;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz k_13;

			mov al, [eax + esi];
			movzx eax, al;
			jmp k_6;

		k_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp k_1x;

		k_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp k_1x;

		k_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp k_1x;

		k_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;

		k_1x:
			//add esi, 2; issue-95の修正で要らなくなった
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja k_6;
			mov eax, NOT_DEF;

		k_6:
			mov ecx, [ebp - 0x20];

			cmp ax, 0x20;
			jz k_2_2;

			cmp ax, 0x100;
			ja k_2_2;

			cmp word ptr[ebp - 0x8C + 2], 0x100;
			jb k_2_5;

		k_2_6:
			mov word ptr[ebp - 0x8C + 2], 9;
			jmp k_2_3;

		k_2_5:
			cmp word ptr[ebp - 0x8C + 2], 9;
			jz k_2_6;

		k_2_2:
			mov word ptr[ebp - 0x8C + 2], ax;

		k_2_3:
			push k_2_v310;
			ret;
		}
	}

	uintptr_t w_2_end_v28;
	__declspec(naked) void w_1_start_v28()
	{
		__asm {
			cmp word ptr[ebp - 0x8C + 2], 0x100;
			jb w_3;

			sub esi, 2;

		w_3:
			mov eax, [ebp + 0x18];//arg_10
			add eax, [ebp - 0x24];

			push w_2_end_v28;
			ret;
		}
	}

	uintptr_t loc_194690F;

	/*-----------------------------------------------*/

	errno_t fix0_hook(RunOptions *options) {
		std::string desc = "fix0";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
			//スタック修正
			// sub esp,7Ch
			byte_pattern::temp_instance().find_pattern("83 EC 7C 53 8B 5D 0C 56 57 8B F1");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x7E, true);
			}
			else return CK2ERROR1;

			// mov al,[eax+esi]
			switch (options->version) {
			case v3_1_0:
			case v3_1_1:
				byte_pattern::temp_instance().find_pattern("8A 04 30 8B 4D");
				if (byte_pattern::temp_instance().has_size(1, desc)) {
					injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), k_1_v310);
					// mov ecx, [ecx+eax*4+OFFSET]
					k_2_v310 = byte_pattern::temp_instance().get_first().address(9);
				}
				else return CK2ERROR1;
				break;
			default:
				byte_pattern::temp_instance().find_pattern("8A 04 30 8B 4D");
				if (byte_pattern::temp_instance().has_size(1, desc)) {
					injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), k_1);
					// mov ecx, [ecx+eax*4+OFFSET]
					k_2 = byte_pattern::temp_instance().get_first().address(9);
				}
				else return CK2ERROR1;
				break;
			}

			switch (options->version) {
			case v3_1_0:
			case v3_1_1:
				break; // issue-95でこの処理はいらなくなった
			case v3_0_X:
				// mov eax,[ebp+arg_10]
				byte_pattern::temp_instance().find_pattern("8B 45 18 03 45 DC 8A 55 20");
				if (byte_pattern::temp_instance().has_size(1, desc)) {
					injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), w_1_start_v28);
					// mov dl,[ebp+arg_18]
					w_2_end_v28 = byte_pattern::temp_instance().get_first().address(6);
				}
				else return CK2ERROR1;
				break;

			default:
				// mov eax,[ebp+arg_10] 
				byte_pattern::temp_instance().find_pattern("8B 45 18 03 45 DC 89 55");
				if (byte_pattern::temp_instance().has_size(1, desc)) {
					injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), w_1_start_v28);
					// mov [ebp+var_14],edx
					w_2_end_v28 = byte_pattern::temp_instance().get_first().address(6);
				}
				else return CK2ERROR1;
				break;
			}

			// 結合するブロックの飛び先
			// cmp eax,[ebp+arc_C]
			byte_pattern::temp_instance().find_pattern("3B 45 14 0F 8F ? 01 00 00 C7");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				loc_194690F = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;
			
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t ee_2_v28;
	uintptr_t ee_3_v28;
	__declspec(naked) void ee_1_1_v28()
	{
		__asm {
			cmp word ptr[ebp - 0x8C + 2], 9;
			jz ee_2_jmp;
			cmp word ptr[ebp - 0x8C + 2], 0x100;
			ja ee_2_jmp;
			cmp ebx, [ebp - 0x18];
			jg ee_3_jmp;
			jmp ee_2_jmp;

		ee_2_jmp:
			push ee_2_v28;
			ret;

		ee_3_jmp:
			push ee_3_v28;
			ret;
		}
	}

	// ブロックの表示がv28と逆になっているので注意
	uintptr_t ee_2_v30;
	uintptr_t ee_3_v30;
	__declspec(naked) void ee_1_1_v30()
	{
		__asm {
			cmp word ptr[ebp - 0x8C + 2], 9;
			jz ee_3_jmp;

			cmp word ptr[ebp - 0x8C + 2], 0x100;
			ja ee_3_jmp;

			mov ecx, dword ptr [ebp - 0x1C];
			cmp dword ptr [ebp - 0x18], ecx;
			jle ee_3_jmp;

			cmp eax, dword ptr [ebp + 0x14]; // arg_C
			jle ee_2_jmp;

			cmp dword ptr [ebp + 0x24], 0; // arg_1C
			jnz ee_3_jmp;
			
		ee_2_jmp: //　左
			push ee_2_v30;
			ret;

		ee_3_jmp: // 右
			push ee_3_v30;
			ret;
		}
	}

	// ブロックの表示がv28と逆になっているので注意
	uintptr_t ee_2_v301;
	uintptr_t ee_3_v301;
	__declspec(naked) void ee_1_1_v301()
	{
		__asm {
			cmp word ptr[ebp - 0x8C + 2], 9;
			jz ee_3_jmp;

			cmp word ptr[ebp - 0x8C + 2], 0x100;
			ja ee_3_jmp;

			mov ebx, dword ptr[ebp - 0x1C];
			cmp ebx, dword ptr [ebp - 0x18];
			jle ee_3_jmp;

			cmp eax, dword ptr[ebp + 0x14]; // arg_C
			jle ee_2_jmp;

			cmp dword ptr[ebp + 0x24], 0; // arg_1C
			jnz ee_3_jmp;

		ee_2_jmp: //　左
			push ee_2_v301;
			ret;

		ee_3_jmp: // 右
			push ee_3_v301;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix1_hook(RunOptions *options) {
		std::string desc = "fix1";

		switch (options->version) {
		case v2_8_X:
			// cmp ebx,[ebp+var_18]
			byte_pattern::temp_instance().find_pattern("3B 5D E8 0F 8F");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), ee_1_1_v28);
				// 左側ブロックの開始位置
				// push esi
				ee_2_v28 = byte_pattern::temp_instance().get_first().address(9);
			}
			else return CK2ERROR1;
			
			//右側のブロックの開始位置
			// push ebx
			byte_pattern::temp_instance().find_pattern("53 FF 75 E8 8D 45 90 C7");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				ee_3_v28 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;
			
			return NOERROR;
		case v3_0_0:
			// cmp ebx,[ebp+var_1C]
			byte_pattern::temp_instance().find_pattern("8B 4D E4 39 4D E8 0F 8E A4 00 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), ee_1_1_v30);
			}
			else return CK2ERROR1;

			//左側のブロックの開始位置
			// push offset asc_XXXXXX
			byte_pattern::temp_instance().find_pattern("68 ? ? ? ? 8D 4D C0 E8 EE 23 07 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				ee_2_v30 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			//右側のブロックの開始位置
			// push offset asc_XXXXXX
			byte_pattern::temp_instance().find_pattern("68 ? ? ? ? 8D 4D C0 E8 59 23 07 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				ee_3_v30 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			return NOERROR;

		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
			// cmp ebx,[ebp+var_1C]
			byte_pattern::temp_instance().find_pattern("8B 5D E4 3B 5D E8 0F 8E A6 00 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), ee_1_1_v301);
			}
			else return CK2ERROR1;

			//左側のブロックの開始位置
			// push offset asc_XXXXXX
			byte_pattern::temp_instance().find_pattern("68 ? ? ? ? 8D 4D C0 E8 ? ? ? ? 53");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				ee_2_v301 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			//右側のブロックの開始位置
			// push offset asc_XXXXXX
			byte_pattern::temp_instance().find_pattern("68 ? ? ? ? 8D 4D C0 E8 ? ? ? ? 56");
			if (byte_pattern::temp_instance().has_size(2, desc)) {
				ee_3_v301 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			return NOERROR;

		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t x_2_v28;
	__declspec(naked) void x_1_v28()
	{
		__asm {
			cmp word ptr[ebp - 0x8C + 2], 0x100;
			jb x_4;

			mov ecx, [eax + 0x10];
			sub ecx, 1;
			mov[eax + 0x10], ecx;

		x_4:
			lea ecx, [ebp - 0x70];

			call func1_v28;

			push x_2_v28;
			ret;
		}
	}

	uintptr_t x_2_v30;
	__declspec(naked) void x_1_v30()
	{
		__asm {
			cmp word ptr[ebp - 0x8C + 2], 0x100;
			jb x_4;

			mov ecx, [eax + 0x10];
			sub ecx, 1;
			mov[eax + 0x10], ecx;

		x_4:
			lea ecx, [ebp - 0x88];

			call func1_v30;

			push x_2_v30;
			ret;
		}
	}

	uintptr_t x_2_v301;
	__declspec(naked) void x_1_v301()
	{
		__asm {
			cmp word ptr[ebp - 0x8C + 2], 0x100;
			jb x_4;

			mov ecx, [eax + 0x10];
			sub ecx, 1;
			mov[eax + 0x10], ecx;

		x_4:
			lea ecx, [ebp - 0x88];

			call func1_v301;

			push x_2_v301;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix2_hook(RunOptions *options) {
		std::string desc = "fix2";

		switch (options->version) {
		case v2_8_X:
			// mov ebx,[ebp+arg_4]
			byte_pattern::temp_instance().find_pattern("8B 5D 0C 8B CB 6A FF 6A 00 50 C6 45 FC 02 E8");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// lea ecx,[ebp+var_70]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x13), x_1_v28);
				// lea ecx,[ebp+var_88]
				x_2_v28 = byte_pattern::temp_instance().get_first().address(0x1B);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_0:
			// lea ecx,[ebp+var_88]
			byte_pattern::temp_instance().find_pattern("8D 8D 78 FF FF FF E8 92 62");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), x_1_v30);
				x_2_v30 = byte_pattern::temp_instance().get_first().address(0xB);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
			// mov eax, [ebp+arg_10]
			byte_pattern::temp_instance().find_pattern("8B 45 18 8B CE 8A 55 20 89 4D E4");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// lea ecx,[ebp+var_88]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(-0x22), x_1_v301);
				x_2_v301 = byte_pattern::temp_instance().get_first().address(0xB - 0x22);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/
	
	__declspec(naked) void x_5_v28()
	{
		__asm {
			cmp word ptr[ebp - 0x8C + 2], 0x100;
			jb x_6;
			sub esi, 1;
		x_6:
			mov[ebp - 0x14], 0;
			push loc_194690F;
			ret;
		}
	}

	__declspec(naked) void x_5_v30()
	{
		__asm {
			cmp word ptr[ebp - 0x8C + 2], 0x100;
			jb x_6;
			sub esi, 1;
		x_6:
			mov[ebp - 0x10], 0;
			push loc_194690F;
			ret;
		}
	}

	__declspec(naked) void x_5_v301()
	{
		__asm {
			cmp word ptr[ebp - 0x8C + 2], 0x100;
			jb x_6;
			sub esi, 1;
		x_6:
			mov[ebp - 0x10], 0;
			push loc_194690F;
			ret;
		}
	}

	__declspec(naked) void x_5_v310()
	{
		__asm {
			mov[ebp - 0x10], 0; // issue-95の修正でesiの変更が要らなくなった
			push loc_194690F;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix3_hook(RunOptions *options) {
		std::string desc = "fix3";

		switch (options->version) {
		case v2_8_X:
			// mov dl,[ebp+arg_18]
			byte_pattern::temp_instance().find_pattern("8A 55 20 89 4D E4 89 75 E8");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov [ebp+var_14],0
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x9), x_5_v28);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_0:
			// ブロックの終端先を変更する
			// mov [ebp+arg_14],0
			byte_pattern::temp_instance().find_pattern("C7 45 EC 00 00 00 00 EB 03");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), x_5_v30);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_X:
			// ブロックの終端先を変更する
			// mov [ebp+arg_14],0
			byte_pattern::temp_instance().find_pattern("C7 45 EC 00 00 00 00 EB 06 8B 5D 0C");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), x_5_v301);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_1_0:
		case v3_1_1:
			// ブロックの終端先を変更する
			// mov [ebp+arg_14],0
			byte_pattern::temp_instance().find_pattern("C7 45 EC 00 00 00 00 EB 06 8B 5D 0C");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), x_5_v310);
			}
			else return CK2ERROR1;
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t fix4_end_v310;
	__declspec(naked) void fix4_start_v310()
	{
		__asm {
			cmp word ptr[ebp - 0x8C + 2], 0x100;
			jb a;

			add esi, 2;

		a:
			inc esi;

			mov     edx, [edi + 0x10];
			cmp esi, edx;

			mov word ptr[ebp - 0x8C + 2], 0;

			push fix4_end_v310;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix4_hook(RunOptions* options) {
		std::string desc = "fix4";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			return NOERROR;
		case v3_1_0:
		case v3_1_1:
			byte_pattern::temp_instance().find_pattern("8B 57 10 46 3B F2 0F 8C 0E FC FF FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov     edx, [edi+10h]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), fix4_start_v310);
				// jl xxxx
				fix4_end_v310 = byte_pattern::temp_instance().get_first().address(6);
			}
			else return CK2ERROR1;
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("main text line break routine");

		result |= func_hook(options);

		result |= fix0_hook(options);

		result |= fixA_hook(options);

		// ブロックの分岐判定処理
		result |= fix1_hook(options);

		// 左側の分岐ブロックの処理の途中１
		result |= fix2_hook(options);

		// 左側の分岐ブロックの処理の途中２
		result |= fix3_hook(options);

		// カウントアップ変更。issue-95への対応
		result |= fix4_hook(options);

		return result;
	}
}