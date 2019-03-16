#include "stdinc.h"
#include "byte_pattern.h"

namespace ButtonAndTooltip
{
	/*-----------------------------------------------*/
	
	errno_t stackSizeChange_hook(RunOptions *options) {
		std::string desc = "stack size change";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			// sub esp,370h
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

	uintptr_t e_5_end_v28;
	__declspec(naked) void e_1_start_v28()
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
			push e_5_end_v28;
			ret;
		}
	}

	uintptr_t f_5_end_v28;
	__declspec(naked) void f_1_start_v28()
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
			
			push f_5_end_v28;
			ret;
		}
	}

	uintptr_t e_5_end_v301;
	__declspec(naked) void e_1_start_v301()
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
			lea ecx, [ebp - 0x88];
			mov byte ptr[ecx], ESCAPE_SEQ_1;
			mov[ecx + 1], ax;
			jmp e_2;

		e_11:
			movzx eax, word ptr[eax + esi + 1];
			lea ecx, [ebp - 0x88]; // 変更された
			mov byte ptr[ecx], ESCAPE_SEQ_2;
			mov[ecx + 1], ax;
			jmp e_2;

		e_12:
			movzx eax, word ptr[eax + esi + 1];
			lea ecx, [ebp - 0x88];
			mov byte ptr[ecx], ESCAPE_SEQ_3;
			mov[ecx + 1], ax;
			jmp e_2;

		e_13:
			movzx eax, word ptr[eax + esi + 1];
			lea ecx, [ebp - 0x88];
			mov byte ptr[ecx], ESCAPE_SEQ_4;
			mov[ecx + 1], ax;
			jmp e_2;

		e_2:
			lea ecx, [ebp - 0x80];
			jmp e_5_jmp;

		e_3:
			mov al, [eax + esi];
			lea ecx, [ebp - 0x80];
			mov byte ptr[ebp - 0x88], al;

		e_5_jmp:
			push e_5_end_v301;
			ret;
		}
	}

	uintptr_t f_5_end_v301;
	__declspec(naked) void f_1_start_v301()
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
			mov ecx, [ebp - 0x88]; // 変更された
			mov[eax], ecx;
			mov byte ptr[eax + 0x10], 3;

		f_3:
			push 0xFFFFFFFF;
			push 0;
			push eax;

			push f_5_end_v301;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func1_2_hook(RunOptions *options) {
		std::string desc = "func1,2";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
			// mov al,[eax+esi]
			byte_pattern::temp_instance().find_pattern("8A 04 30 88 85 3C FF FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), e_1_start_v28);
				// push [ebp+var_C4]
				e_5_end_v28 = byte_pattern::temp_instance().get_first().address(9);

				// push 0FFFFFFFFh 
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x14), f_1_start_v28);
				// lea ecx,[ebp+var_AC]
				f_5_end_v28 = byte_pattern::temp_instance().get_first().address(0x19);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_X:
			// mov al,[eax+esi]
			byte_pattern::temp_instance().find_pattern("8A 04 30 88 85 78 FF FF FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), e_1_start_v301);
				// push [ebp+var_88]
				e_5_end_v301 = byte_pattern::temp_instance().get_first().address(9);

				// push 0FFFFFFFFh 
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x14), f_1_start_v301);
				// lea ecx,[ebp+var_B4] 
				f_5_end_v301 = byte_pattern::temp_instance().get_first().address(0x19);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t g_5_end_v28;
	__declspec(naked) void g_1_start_v28()
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

			push g_5_end_v28;
			ret;
		}
	}

	uintptr_t g_5_end_v301;
	__declspec(naked) void g_1_start_v301()
	{
		__asm {
			cmovnb eax, edi;
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

			push g_5_end_v301;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func3_hook(RunOptions *options) {
		std::string desc = "func3";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
			// cmovnb eax,edx
			byte_pattern::temp_instance().find_pattern("0F 43 C2 0F B6 04 30 8B 84 83");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), g_1_start_v28);
				// mov eax,[ebx+eax*4+0A4h]
				g_5_end_v28 = byte_pattern::temp_instance().get_first().address(7);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_X:
			// cmovnb  eax, edi
			byte_pattern::temp_instance().find_pattern("0F 43 C7 0F B6 04 30 8B 8C 81");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), g_1_start_v301);
				// mov ecx, [ecx+eax*4+0A4h]
				g_5_end_v301 = byte_pattern::temp_instance().get_first().address(7);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t func4_end_v28;
	uintptr_t func4_end2_v28;
	__declspec(naked) void func4_start_v28()
	{
		__asm {
			mov byte ptr[ebp - 0x5C], 0;
			jz h_2_jmp;
			cmp[ebp - 0x380], 0x100;
			jg h_2_jmp;

			push func4_end2_v28;
			ret;

		h_2_jmp:
			push func4_end_v28;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func4_hook(RunOptions *options) {
		std::string desc = "func4";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
			// cmp [ebp+var_5C],0
			byte_pattern::temp_instance().find_pattern("83 7D A4 00 0F 85 ? ? ? ? 83");
			if (byte_pattern::temp_instance().has_size(1,desc + " start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func4_start_v28);

				// mov eax,[ebp+arg_20]
				func4_end_v28 = byte_pattern::temp_instance().get_first().address(10);
			}
			else return CK2ERROR1;

			// inc esi
			byte_pattern::temp_instance().find_pattern("46 3B 75 E4 0F 8C AA F9");
			if (byte_pattern::temp_instance().has_size(1, desc + " end2")) {
				func4_end2_v28 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			return NOERROR;

		case v3_0_X:
			// cmp [ebp+var_5C],0
			byte_pattern::temp_instance().find_pattern("83 7D A4 00 0F 85 ? ? ? ? 83");
			if (byte_pattern::temp_instance().has_size(1, desc + " start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func4_start_v28);

				// mov eax,[ebp+arg_20]
				func4_end_v28 = byte_pattern::temp_instance().get_first().address(10);
			}
			else return CK2ERROR1;

			// inc esi
			// このパターンがどうしても引っ掛けられなかった
			byte_pattern::temp_instance().find_pattern("46 3B 75 E4 0F 8C 9A F9 FF FF");
			if (byte_pattern::temp_instance().has_size(1, desc + " end2")) {
				func4_end2_v28 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			return NOERROR;

		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t i_6_end_v28;
	__declspec(naked) void i_1_start_v28()
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
			push i_6_end_v28;
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

			push i_6_end_v28;
			ret;
		}
	}

	uintptr_t i_6_end_v301;
	__declspec(naked) void i_1_start_v301()
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
			push i_6_end_v301;
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
			mov[ebp - 0x18], ebx;

			push i_6_end_v301;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func5_hook(RunOptions *options) {
		std::string desc = "func5";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
			// cmovnb eax,edi
			byte_pattern::temp_instance().find_pattern("0F 43 C7 0F B6 04 18 8B");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), i_1_start_v28);
				// mov eax, [edx+eax*4+A4h]
				i_6_end_v28 = byte_pattern::temp_instance().get_first().address(7);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_X:
			// cmovnb eax,edi
			byte_pattern::temp_instance().find_pattern("0F 43 C7 0F B6 04 18 8B");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), i_1_start_v301);
				// mov eax, [edx+eax*4+A4h]
				i_6_end_v301 = byte_pattern::temp_instance().get_first().address(7);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t stackClear_hook(RunOptions *options) {
		std::string desc = "stack clear";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			// lea esp,[ebp - 388h]
			byte_pattern::temp_instance().find_pattern("8D A5 78 FC FF FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x70, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("button and tooltip");

		// stack size change
		result |= stackSizeChange_hook(options);
		// 
		result |= func1_2_hook(options);
		// 
		result |= func3_hook(options);
		//
		result |= func4_hook(options);
		//
		result |= func5_hook(options);
		//
		result |= stackClear_hook(options);

		return result;
	}

}
