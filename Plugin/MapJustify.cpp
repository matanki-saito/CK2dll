#include "stdinc.h"
#include "byte_pattern.h"

namespace MapJustify {
	/*-----------------------------------------------*/

	uintptr_t loc_12CDF48_v28;
	uintptr_t loc_12CDF51_v28;
	__declspec(naked) void s_1_v28()
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

			push loc_12CDF48_v28;
			ret;

		s_2:
			mov ecx, 3;
			cmp byte ptr[ebp - 0xCC], 0x10;
			lea eax, [ebp - 0xE0];
			cmovnb eax, [ebp - 0xE0];
			movzx ax, word ptr[eax + esi + 1];
			mov word ptr[ebp - 0x1C + 1], ax;
			add esi, 2;

			push loc_12CDF51_v28;
			ret;
		}
	}

	uintptr_t loc_12CDF48_v30;
	uintptr_t loc_12CDF51_v30;
	__declspec(naked) void s_1_v30()
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

			lea ecx, dword ptr [ebp - 0x10]; // 1C -> 10
			lea edx, dword ptr [ecx + 1];

			push loc_12CDF48_v30;
			ret;

		s_2:
			mov ecx, 3;
			cmp byte ptr[ebp - 0xC4], 0x10; // CC -> C4
			lea eax, dword ptr [ebp - 0xD8]; // E0 -> D8
			cmovnb eax, dword ptr [ebp - 0xD8]; // E0 -> D8
			movzx ax, word ptr[eax + esi + 1];
			mov word ptr[ebp - 0x10 + 1], ax; // 1C -> 10
			add esi, 2;

			push loc_12CDF51_v30;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func1_hook(RunOptions *options) {
		std::string desc = "func1";

		switch (options->version) {
		case v2_8_X:
			// lea ecx,[ebp+var_1C]
			byte_pattern::temp_instance().find_pattern("8D 4D E4 8D 51 01 8A 01 41");
			if (byte_pattern::temp_instance().has_size(1, desc + "start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), s_1_v28);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("8A 01 41 84 C0 75 F9 2B CA 51 8D 45 E4 50");
			// mov al,[ecx]
			if (byte_pattern::temp_instance().has_size(2, desc + " end1")) {
				loc_12CDF48_v28 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			//push ecx
			byte_pattern::temp_instance().find_pattern("51 8D 45 E4 50 8D 8D 48");
			if (byte_pattern::temp_instance().has_size(2, desc + " end2")) {
				loc_12CDF51_v28 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			return NOERROR;
		case v3_0_0:
		case v3_0_X:
			// lea ecx,[ebp+var_10]
			byte_pattern::temp_instance().find_pattern("8D 4D F0 8D 51 01 8A 01 41");
			if (byte_pattern::temp_instance().has_size(1, desc + "start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), s_1_v30);
			}
			else return CK2ERROR1;

			// mov al,[ecx]
			byte_pattern::temp_instance().find_pattern("8A 01 41 84 C0 75 F9 2B CA 51 8D 45 F0 50");
			if (byte_pattern::temp_instance().has_size(2, desc + " end1")) {
				loc_12CDF48_v30 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			// push ecx
			byte_pattern::temp_instance().find_pattern("51 8D 45 F0 50 8D 8D 50");
			if (byte_pattern::temp_instance().has_size(2, desc + " end2")) {
				loc_12CDF51_v30 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t t_2_v28;
	uintptr_t t_3_v28;
	__declspec(naked) void t_1_v28()
	{
		__asm {
			cmp esi, ebx;
			jz t_3_jmp;

			push 0xFFFFFFFF;
			push 0;
			lea eax, [ebp - 0x178];

			push t_2_v28;
			ret;

		t_3_jmp:
			push t_3_v28;
			ret;
		}
	};

	uintptr_t t_2_v30;
	uintptr_t t_3_v30;
	__declspec(naked) void t_1_v30()
	{
		__asm {
			cmp esi, edi; // ebx -> edi
			jz t_3_jmp;

			push 0xFFFFFFFF;
			push 0;
			lea eax, [ebp - 0x16C]; // •ÏX‚³‚ê‚½

			push t_2_v30;
			ret;

		t_3_jmp:
			push t_3_v30;
			ret;
		}
	};

	/*-----------------------------------------------*/

	errno_t func2_hook(RunOptions *options) {
		std::string desc = "func2";

		switch (options->version) {
		case v2_8_X:
			// push 0xFFFFFFFF
			byte_pattern::temp_instance().find_pattern("6A FF 6A 00 8D 85 88 FE FF FF 50");
			if (byte_pattern::temp_instance().has_size(1,desc + " start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), t_1_v28);
				// push eax
				t_2_v28 = byte_pattern::temp_instance().get_first().address(10);
			}
			else return CK2ERROR1;

			// mov esi, [ebp+arg_0]
			byte_pattern::temp_instance().find_pattern("8B 75 08 8D 45 E0 50 8D");
			if (byte_pattern::temp_instance().has_size(1, desc + " end2")) {
				t_3_v28 = byte_pattern::temp_instance().get_first().address(0);
			}
			else return CK2ERROR1;

			return NOERROR;
		case v3_0_0:
		case v3_0_X:
			// push 0xFFFFFFFF
			byte_pattern::temp_instance().find_pattern("6A FF 6A 00 8D 85 94 FE FF FF 50");
			if (byte_pattern::temp_instance().has_size(1, desc + " start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), t_1_v30);
				// push eax
				t_2_v30 = byte_pattern::temp_instance().get_first().address(10);
			}
			else return CK2ERROR1;

			// mov esi,[ebp+arg_0]
			byte_pattern::temp_instance().find_pattern("8B 75 08 8D 45 E8 50 8D");
			if (byte_pattern::temp_instance().has_size(1, desc + " end2")) {
				t_3_v30 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t r_4_v28;
	__declspec(naked) void r_1_v28()
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
			
			push r_4_v28;
			ret;
		}
	};

	uintptr_t r_4_v30;
	__declspec(naked) void r_1_v30()
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
			mov eax, [esi + eax * 4]; // v28¨v30‚Åedi¨esi‚É‚È‚Á‚½

			push r_4_v30;
			ret;
		}
	};

	/*-----------------------------------------------*/

	errno_t func3_hook(RunOptions *options) {
		std::string desc = "func3";

		switch (options->version) {
		case v2_8_X:
			// movzx eax,byte ptr [ecx+eax]
			byte_pattern::temp_instance().find_pattern("0F B6 04 01 8B 04 87 85");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), r_1_v28);
				// test eax,eax
				r_4_v28 = byte_pattern::temp_instance().get_first().address(0x07);
			}
			else return CK2ERROR1;
			return NOERROR;
		case v3_0_0:
		case v3_0_X:
			// movzx eax,byte ptr [ecx+eax]
			byte_pattern::temp_instance().find_pattern("0F B6 04 01 8B 04 86 85 C0");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), r_1_v30);
				// test eax,eax
				r_4_v30 = byte_pattern::temp_instance().get_first().address(0x07);
			}
			else return CK2ERROR1;
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("map font justify");

		// 1
		result |= func1_hook(options);
		// 2
		result |= func2_hook(options);
		// 3
		result |= func3_hook(options);

		return result;
	}
}