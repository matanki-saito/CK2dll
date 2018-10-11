#include "stdinc.h"
#include "byte_pattern.h"

namespace ButtonAndTooltip
{
	/*-----------------------------------------------*/

	errno_t stackSizeChange_hook(CK2Version version) {
		std::string desc = "stack size change";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("81 EC 70 03 00 00 8B");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x78, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t e_5;
	__declspec(naked) void e_1()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz e_10;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz e_11;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz e_12;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz e_13;

			jmp e_3;

		e_10:
			movzx eax, word ptr[eax + esi + 1];
			lea ecx, [ebp - 0xC4];
			mov byte ptr[ecx], ESCAPE_SEQ_1;
			mov[ecx + 1], ax;
			jmp e_2;

		e_11:
			movzx eax, word ptr[eax + esi + 1];
			lea ecx, [ebp - 0xC4];
			mov byte ptr[ecx], ESCAPE_SEQ_2;
			mov[ecx + 1], ax;
			jmp e_2;

		e_12:
			movzx eax, word ptr[eax + esi + 1];
			lea ecx, [ebp - 0xC4];
			mov byte ptr[ecx], ESCAPE_SEQ_3;
			mov[ecx + 1], ax;
			jmp e_2;

		e_13:
			movzx eax, word ptr[eax + esi + 1];
			lea ecx, [ebp - 0xC4];
			mov byte ptr[ecx], ESCAPE_SEQ_4;
			mov[ecx + 1], ax;
			jmp e_2;

		e_2:
			lea ecx, [ebp - 0x80];
			jmp e_5_jmp;

		e_3:
			mov al, [eax + esi];
			lea ecx, [ebp - 0x80];
			mov byte ptr[ebp - 0xC4], al;
		
		e_5_jmp:
			push e_5;
			ret;
		}
	}

	uintptr_t f_5;
	__declspec(naked) void f_1()
	{
		__asm {
			cmp byte ptr[eax], ESCAPE_SEQ_1;
			jz f_2;

			cmp byte ptr[eax], ESCAPE_SEQ_2;
			jz f_2;

			cmp byte ptr[eax], ESCAPE_SEQ_3;
			jz f_2;

			cmp byte ptr[eax], ESCAPE_SEQ_4;
			jz f_2;

			jmp f_3;

		f_2:
			mov ecx, [ebp - 0xC4];
			mov[eax], ecx;
			mov byte ptr[eax + 0x10], 3;

		f_3:
			push 0xFFFFFFFF;
			push 0;
			push eax;
			
			push f_5;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func1_2_hook(CK2Version version) {
		std::string desc = "func1,2";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("8A 04 30 88 85 3C FF FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), e_1);
					e_5 = byte_pattern::temp_instance().get_first().address(9);

					injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x14), f_1);
					f_5 = byte_pattern::temp_instance().get_first().address(0x19);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t g_5;
	__declspec(naked) void g_1()
	{
		__asm {
			cmovnb eax, edx;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz g_10;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz g_11;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz g_12;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz g_13;

			jmp g_3;

		g_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp g_2;

		g_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp g_2;

		g_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp g_2;

		g_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;
			jmp g_2;
		
		g_2:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja g_4;
			mov eax, NOT_DEF;
		
		g_4:
			add esi, 2;
			jmp g_6;

		g_3:
			movzx eax, byte ptr[eax + esi];

		g_6:
			mov[ebp - 0x380], eax;

			push g_5;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func3_hook(CK2Version version) {
		std::string desc = "func3";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("0F 43 C2 0F B6 04 30 8B 84 83");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), g_1);
				g_5 = byte_pattern::temp_instance().get_first().address(7);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t h_2;
	uintptr_t loc_19417DE;
	__declspec(naked) void h_1()
	{
		__asm {
			mov byte ptr[ebp - 0x5C], 0;
			jz h_2_jmp;
			cmp[ebp - 0x380], 0x100;
			jg h_2_jmp;

			push loc_19417DE;
			ret;

		h_2_jmp:
			push h_2;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func4_hook(CK2Version version) {
		std::string desc = "func4";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("83 7D A4 00 0F 85 9B");
			if (byte_pattern::temp_instance().has_size(1,desc + " start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), h_1);
				h_2 = byte_pattern::temp_instance().get_first().address(10);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("46 3B 75 E4 0F 8C AA F9");
			if (byte_pattern::temp_instance().has_size(1, desc + " end2")) {
				loc_19417DE = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t stackClear_hook(CK2Version version) {
		std::string desc = "stack clear";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("8D A5 78 FC FF FF");
			if (byte_pattern::temp_instance().has_size(1,desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x70, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t i_6;
	__declspec(naked) void i_1()
	{
		__asm {
			cmovnb eax, edi;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_1;
			jz i_10;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_2;
			jz i_11;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_3;
			jz i_12;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_4;
			jz i_13;

			movzx eax, byte ptr[eax + ebx];
			push i_6;
			ret;

		i_10:
			movzx eax, word ptr[eax + ebx + 1];
			jmp i_3;

		i_11:
			movzx eax, word ptr[eax + ebx + 1];
			sub eax, SHIFT_2;
			jmp i_3;

		i_12:
			movzx eax, word ptr[eax + ebx + 1];
			add eax, SHIFT_3;
			jmp i_3;

		i_13:
			movzx eax, word ptr[eax + ebx + 1];
			add eax, SHIFT_4;

		i_3:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja i_4;
			mov eax, NOT_DEF;
		i_4:
			add ebx, 2;
			mov[ebp - 0x14], ebx;

			push i_6;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func5_hook(CK2Version version) {
		std::string desc = "func5";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("0F 43 C7 0F B6 04 18 8B");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), i_1);
				i_6 = byte_pattern::temp_instance().get_first().address(7);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(CK2Version version) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("button and tooltip");

		// stack size change
		result |= stackSizeChange_hook(version);
		// 
		result |= func1_2_hook(version);
		// 
		result |= func3_hook(version);
		//
		result |= func4_hook(version);
		//
		result |= func5_hook(version);
		//
		result |= stackClear_hook(version);

		return result;
	}

}
