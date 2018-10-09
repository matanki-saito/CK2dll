#include "stdinc.h"
#include "byte_pattern.h"

namespace MapJustify {
	/*-----------------------------------------------*/

	uintptr_t loc_12CDF48;
	uintptr_t loc_12CDF51;
	__declspec(naked) void s_1()
	{
		__asm {
			cmp al, ESCAPE_SEQ_1;
			jz s_2;

			cmp al, ESCAPE_SEQ_2;
			jz s_2;

			cmp al, ESCAPE_SEQ_3;
			jz s_2;

			cmp al, ESCAPE_SEQ_4;
			jz s_2;

			lea ecx, [ebp - 0x1C];
			lea edx, [ecx + 1];

			push loc_12CDF48;
			ret;

		s_2:
			mov ecx, 3;
			cmp byte ptr[ebp - 0xCC], 0x10;
			lea eax, [ebp - 0xE0];
			cmovnb eax, [ebp - 0xE0];
			movzx ax, word ptr[eax + esi + 1];
			mov word ptr[ebp - 0x1C + 1], ax;
			add esi, 2;

			push loc_12CDF51;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func1_hook(CK2Version version) {
		std::string desc = "func1";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("8D 4D E4 8D 51 01 8A 01 41");
			if (byte_pattern::temp_instance().has_size(1, desc + "start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), s_1);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("8A 01 41 84 C0 75 F9 2B CA 51 8D 45 E4 50");
			if (byte_pattern::temp_instance().has_size(2, desc + " end1")) {
				loc_12CDF48 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("51 8D 45 E4 50 8D 8D 48");
			if (byte_pattern::temp_instance().has_size(2, desc + " end2")) {
				loc_12CDF51 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t t_2;
	uintptr_t t_3;
	__declspec(naked) void t_1()
	{
		__asm {
			cmp esi, ebx;
			jz t_3_jmp;

			push 0xFFFFFFFF;
			push 0;
			lea eax, [ebp - 0x178];

			push t_2;
			ret;

		t_3_jmp:
			push t_3;
			ret;
		}
	};

	/*-----------------------------------------------*/

	errno_t func2_hook(CK2Version version) {
		std::string desc = "func2";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("6A FF 6A 00 8D 85 88 FE FF FF 50");
			if (byte_pattern::temp_instance().has_size(1,desc + " start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), t_1);
				t_2 = byte_pattern::temp_instance().get_first().address(10);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("8B 75 08 8D 45 E0 50 8D");
			if (byte_pattern::temp_instance().has_size(1, desc + " end2")) {
				t_3 = byte_pattern::temp_instance().get_first().address(0);
			}
			else return CK2ERROR1;

			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t r_4;
	__declspec(naked) void r_1()
	{
		__asm {
			cmp byte ptr[ecx + eax], ESCAPE_SEQ_1;
			jz r_10;

			cmp byte ptr[ecx + eax], ESCAPE_SEQ_2;
			jz r_11;

			cmp byte ptr[ecx + eax], ESCAPE_SEQ_3;
			jz r_12;

			cmp byte ptr[ecx + eax], ESCAPE_SEQ_4;
			jz r_13;

			jmp r_2;

		r_10:
			movzx eax, word ptr[ecx + eax + 1];
			jmp r_1x;

		r_11:
			movzx eax, word ptr[ecx + eax + 1];
			sub eax, SHIFT_2;
			jmp r_1x;

		r_12:
			movzx eax, word ptr[ecx + eax + 1];
			add eax, SHIFT_3;
			jmp r_1x;

		r_13:
			movzx eax, word ptr[ecx + eax + 1];
			add eax, SHIFT_4;
			jmp r_1x;

		r_2:
			movzx eax, byte ptr[ecx + eax];
			jmp r_3;

		r_1x:
			add ecx, 2;
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja r_3;
			mov eax, NOT_DEF;
		r_3:
			mov eax, [edi + eax * 4];
			
			push r_4;
			ret;
		}
	};

	/*-----------------------------------------------*/

	errno_t func3_hook(CK2Version version) {
		std::string desc = "func3";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("0F B6 04 01 8B 04 87 85");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), r_1);
				r_4 = byte_pattern::temp_instance().get_first().address(0x07);
			}
			else return CK2ERROR1;
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(CK2Version version) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("map font justify");

		// 1
		result |= func1_hook(version);
		// 2
		result |= func2_hook(version);
		// 3
		result |= func3_hook(version);

		return result;
	}
}