#include "stdinc.h"
#include "byte_pattern.h"

namespace Unk1 {

	/*-----------------------------------------------*/

	uintptr_t dd_5;
	uintptr_t dd_4;
	__declspec(naked) void dd_1()
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
			mov[ebp - 0x1C], eax;
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

	uintptr_t w_2;
	__declspec(naked) void w_1()
	{
		__asm {
			cmp word ptr [ebp - 0x8C + 2], 0x100;
			jb w_3;
	
			sub esi, 2;
	
		w_3:
			mov eax, [ebp + 0x18];//arg_10
			add eax, [ebp - 0x24];
	
			push w_2;
			ret;
		}
	}

	uintptr_t ee_2;
	uintptr_t ee_3;
	__declspec(naked) void ee_1_1()
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
			push ee_2;
			ret;
	
		ee_3_jmp:
			push ee_3;
			ret;
		}
	}

	// dummy
	void __fastcall X_f1(void *p) {
		__asm {
			nop;
			nop;
			nop;
			nop;
			nop;
			nop;
			nop;
		}
	}
	
	uintptr_t x_2;
	__declspec(naked) void x_1()
	{
		__asm {
			cmp word ptr[ebp - 0x8C + 2], 0x100;
			jb x_4;
	
			mov ecx, [eax + 0x10];
			sub ecx, 1;
			mov[eax + 0x10], ecx;
	
		x_4:
			lea ecx, [ebp - 0x70];
	
			call X_f1;
				
			push x_2;
			ret;
		}
	}

	uintptr_t loc_194690F;
	__declspec(naked) void x_5()
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

	/*-----------------------------------------------*/

	errno_t fix1_hook(CK2Version version) {
		std::string desc = "fix1";

		switch (version) {
		case v2_8_X:
			/* sub_19465B0　？ */
			//スタック修正
			byte_pattern::temp_instance().find_pattern("83 EC 7C 53 8B 5D 0C 56 57");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x7E, true);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("80 F9 20 0F 44 C6 89 45");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), dd_1);
				dd_5 = byte_pattern::temp_instance().get_first().address(14);
				dd_4 = byte_pattern::temp_instance().get_first().address(0x12);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("8A 04 30 8B 4D");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), k_1);
				k_2 = byte_pattern::temp_instance().get_first().address(9);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("8B 45 18 03 45 DC 89 55");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), w_1);
				w_2 = byte_pattern::temp_instance().get_first().address(6);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("3B 5D E8 0F 8F");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), ee_1_1);
				ee_2 = byte_pattern::temp_instance().get_first().address(9);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("53 FF 75 E8 8D 45 90 C7");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				ee_3 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("8B 5D 0C 8B CB 6A FF 6A 00 50 C6 45 FC 02 E8");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x13), x_1);
				x_2 = byte_pattern::temp_instance().get_first().address(0x1B);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("56 8B F1 8B 46 14 83 F8 10 72 0E");
			if (byte_pattern::temp_instance().has_size(2, desc)) {
				injector::MakeJMP(X_f1, byte_pattern::temp_instance().get_first().address(0));
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("8A 55 20 89 4D E4 89 75 E8");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x9), x_5);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("3B 45 14 0F 8F 70 01 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				loc_194690F = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(CK2Version version) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("unk1");

		result |= fix1_hook(version);

		return result;
	}
}