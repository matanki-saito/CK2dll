#include "stdinc.h"
#include "byte_pattern.h"


namespace MapView
{
	/*-----------------------------------------------*/

	uintptr_t p_5_end_v28;
	__declspec(naked) void p_1_start_v28()
	{
		__asm {
			cmp byte ptr[eax + ebx], ESCAPE_SEQ_1;
			jz p_10;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_2;
			jz p_11;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_3;
			jz p_12;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_4;
			jz p_13;

			mov al, [eax + ebx];
			lea ecx, [ebp - 0xFC];
			mov byte ptr[ebp - 0x34], al;

			push p_5_end_v28;
			ret;

		p_10:
			movzx eax, word ptr[eax + ebx + 1];
			lea ecx, [ebp - 0x34];
			mov byte ptr[ecx], ESCAPE_SEQ_1;
			mov[ecx + 1], ax;
			jmp p_1x;

		p_11:
			movzx eax, word ptr[eax + ebx + 1];
			lea ecx, [ebp - 0x34];
			mov byte ptr[ecx], ESCAPE_SEQ_2;
			mov[ecx + 1], ax;
			jmp p_1x;

		p_12:
			movzx eax, word ptr[eax + ebx + 1];
			lea ecx, [ebp - 0x34];
			mov byte ptr[ecx], ESCAPE_SEQ_3;
			mov[ecx + 1], ax;
			jmp p_1x;

		p_13:
			movzx eax, word ptr[eax + ebx + 1];
			lea ecx, [ebp - 0x34];
			mov byte ptr[ecx], ESCAPE_SEQ_4;
			mov[ecx + 1], ax;

		p_1x:
			lea ecx, [ebp - 0xFC];

			push p_5_end_v28;
			ret;
		}
	}

	uintptr_t q_4_end_v28;
	__declspec(naked) void q_1_start_v28()
	{
		__asm {
			cmp byte ptr[eax], ESCAPE_SEQ_1;
			jz q_2;

			cmp byte ptr[eax], ESCAPE_SEQ_2;
			jz q_2;

			cmp byte ptr[eax], ESCAPE_SEQ_3;
			jz q_2;

			cmp byte ptr[eax], ESCAPE_SEQ_4;
			jz q_2;

			jmp q_3;

		q_2:
			mov ecx, [ebp - 0x34];
			mov[eax], ecx;
			mov byte ptr[eax + 0x10], 3;

		q_3:
			push 0xFFFFFFFF;
			push 0;
			push eax;

			push q_4_end_v28;
			ret;
		}
	}

	uintptr_t p_5_end_v301;
	__declspec(naked) void p_1_start_v301()
	{
		__asm {
			cmp byte ptr[eax + ebx], ESCAPE_SEQ_1;
			jz p_10;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_2;
			jz p_11;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_3;
			jz p_12;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_4;
			jz p_13;

			mov al, [eax + ebx];
			lea ecx, [ebp - 0x100]; // 変更された
			mov byte ptr[ebp - 0x3C], al;

			push p_5_end_v301;
			ret;

		p_10:
			movzx eax, word ptr[eax + ebx + 1];
			lea ecx, [ebp - 0x3C];
			mov byte ptr[ecx], ESCAPE_SEQ_1;
			mov[ecx + 1], ax;
			jmp p_1x;

		p_11:
			movzx eax, word ptr[eax + ebx + 1];
			lea ecx, [ebp - 0x3C];
			mov byte ptr[ecx], ESCAPE_SEQ_2;
			mov[ecx + 1], ax;
			jmp p_1x;

		p_12:
			movzx eax, word ptr[eax + ebx + 1];
			lea ecx, [ebp - 0x3C];
			mov byte ptr[ecx], ESCAPE_SEQ_3;
			mov[ecx + 1], ax;
			jmp p_1x;

		p_13:
			movzx eax, word ptr[eax + ebx + 1];
			lea ecx, [ebp - 0x3C];
			mov byte ptr[ecx], ESCAPE_SEQ_4;
			mov[ecx + 1], ax;

		p_1x:
			lea ecx, [ebp - 0x100]; // 変更された

			push p_5_end_v301;
			ret;
		}
	}

	uintptr_t q_4_end_v301;
	__declspec(naked) void q_1_start_v301()
	{
		__asm {
			cmp byte ptr[eax], ESCAPE_SEQ_1;
			jz q_2;

			cmp byte ptr[eax], ESCAPE_SEQ_2;
			jz q_2;

			cmp byte ptr[eax], ESCAPE_SEQ_3;
			jz q_2;

			cmp byte ptr[eax], ESCAPE_SEQ_4;
			jz q_2;

			jmp q_3;

		q_2:
			mov ecx, [ebp - 0x3C]; // 変更された
			mov[eax], ecx;
			mov byte ptr[eax + 0x10], 3;

		q_3:
			push 0xFFFFFFFF;
			push 0;
			push eax;

			push q_4_end_v301;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func1_2_hook(RunOptions *options) {
		std::string desc = "func1,2";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
			// mov al,[eax+ebx]
			byte_pattern::temp_instance().find_pattern("8A 04 18 8D 8D 04 FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), p_1_start_v28);
				// push [ebp+var_34]
				p_5_end_v28 = byte_pattern::temp_instance().get_first().address(12);
	
				// 0xFFFFFFFF
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x14), q_1_start_v28);
				// lea ecx, [ebp+var_B4]
				q_4_end_v28 = byte_pattern::temp_instance().get_first().address(0x19);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_X:
			// mov al,[eax+ebx]
			byte_pattern::temp_instance().find_pattern("8A 04 18 8D 8D 00 FF FF FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), p_1_start_v301);
				// push [ebp+var_3C]
				p_5_end_v301 = byte_pattern::temp_instance().get_first().address(12);

				// 0xFFFFFFFF
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x14), q_1_start_v301);
				// lea ecx, [ebp+var_B8]
				q_4_end_v301 = byte_pattern::temp_instance().get_first().address(0x19);
			}
			else return CK2ERROR1;
			return NOERROR;

		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t o_5_end_v28;
	__declspec(naked) void o_1_start_v28()
	{
		__asm {
			cmp byte ptr[eax + ebx], ESCAPE_SEQ_1;
			jz o_10;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_2;
			jz o_11;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_3;
			jz o_12;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_4;
			jz o_13;

			jmp o_3;

		o_10:
			movzx eax, word ptr[eax + ebx + 1];
			jmp o_1x;

		o_11:
			movzx eax, word ptr[eax + ebx + 1];
			sub eax, SHIFT_2;
			jmp o_1x;

		o_12:
			movzx eax, word ptr[eax + ebx + 1];
			add eax, SHIFT_3;
			jmp o_1x;

		o_13:
			movzx eax, word ptr[eax + ebx + 1];
			add eax, SHIFT_4;
	
		o_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja o_2;
			mov eax, NOT_DEF;

		o_2:
			add ebx, 2;
			jmp o_4;

		o_3:
			movzx eax, byte ptr[eax + ebx];

		o_4:
			mov edx, [ebp - 0x20];

			push o_5_end_v28;
			ret;
		}
	}

	uintptr_t o_5_end_v301;
	__declspec(naked) void o_1_start_v301()
	{
		__asm {
			cmp byte ptr[eax + ebx], ESCAPE_SEQ_1;
			jz o_10;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_2;
			jz o_11;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_3;
			jz o_12;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_4;
			jz o_13;

			jmp o_3;

		o_10:
			movzx eax, word ptr[eax + ebx + 1];
			jmp o_1x;

		o_11:
			movzx eax, word ptr[eax + ebx + 1];
			sub eax, SHIFT_2;
			jmp o_1x;

		o_12:
			movzx eax, word ptr[eax + ebx + 1];
			add eax, SHIFT_3;
			jmp o_1x;

		o_13:
			movzx eax, word ptr[eax + ebx + 1];
			add eax, SHIFT_4;

		o_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja o_2;
			mov eax, NOT_DEF;

		o_2:
			add ebx, 2;
			mov dword ptr[ebp - 0x24], ebx; // 追加した
			jmp o_4;

		o_3:
			movzx eax, byte ptr[eax + ebx];

		o_4:
			mov edx, [ebp - 0x18]; // 変更

			push o_5_end_v301;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func3_hook(RunOptions *options) {
		std::string desc = "func3";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
			// movzx eax, byte ptr [eax+ebx]
			byte_pattern::temp_instance().find_pattern("0F B6 04 18 8B 55 E0");
			if (byte_pattern::temp_instance().has_size(1,desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), o_1_start_v28);
				// mov edx,[edx+eax*4+OFFSET]
				o_5_end_v28 = byte_pattern::temp_instance().get_first().address(7);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_X:
			// movzx eax, byte ptr [eax+ebx]
			byte_pattern::temp_instance().find_pattern("0F B6 04 18 8B 55 E8 8B 84 82 A4 00 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), o_1_start_v301);
				// mov edx,[edx+eax*4+OFFSET]
				o_5_end_v301 = byte_pattern::temp_instance().get_first().address(7);
			}
			else return CK2ERROR1;
			return NOERROR;

		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t n_4_v28;
	__declspec(naked) void n_1_v28()
	{
		__asm {
			cmp byte ptr[eax + ecx], ESCAPE_SEQ_1;
			jz n_10;

			cmp byte ptr[eax + ecx], ESCAPE_SEQ_2;
			jz n_11;

			cmp byte ptr[eax + ecx], ESCAPE_SEQ_3;
			jz n_12;

			cmp byte ptr[eax + ecx], ESCAPE_SEQ_4;
			jz n_13;

			jmp n_3;

		n_10:
			movzx eax, word ptr[eax + ecx + 1];
			jmp n_1x;

		n_11:
			movzx eax, word ptr[eax + ecx + 1];
			sub eax, SHIFT_2;
			jmp n_1x;

		n_12:
			movzx eax, word ptr[eax + ecx + 1];
			add eax, SHIFT_3;
			jmp n_1x;

		n_13:
			movzx eax, word ptr[eax + ecx + 1];
			add eax, SHIFT_4;

		n_1x:
			add ecx, 2;
			movzx eax, ax;
			mov[ebp - 0x14], ecx;

			cmp eax, NO_FONT;
			ja n_2;
			mov eax, NOT_DEF;

		n_2:
			jmp n_5;

		n_3:
			movzx eax, byte ptr[eax + ecx];
		n_5:
			mov edx, [edx + eax * 4 + 0x8C];

			push n_4_v28;
			ret;
		}
	}

	uintptr_t n_4_v30;
	__declspec(naked) void n_1_v30()
	{
		__asm {
			cmp byte ptr[eax + ecx], ESCAPE_SEQ_1;
			jz n_10;

			cmp byte ptr[eax + ecx], ESCAPE_SEQ_2;
			jz n_11;

			cmp byte ptr[eax + ecx], ESCAPE_SEQ_3;
			jz n_12;

			cmp byte ptr[eax + ecx], ESCAPE_SEQ_4;
			jz n_13;

			jmp n_3;

		n_10:
			movzx eax, word ptr[eax + ecx + 1];
			jmp n_1x;

		n_11:
			movzx eax, word ptr[eax + ecx + 1];
			sub eax, SHIFT_2;
			jmp n_1x;

		n_12:
			movzx eax, word ptr[eax + ecx + 1];
			add eax, SHIFT_3;
			jmp n_1x;

		n_13:
			movzx eax, word ptr[eax + ecx + 1];
			add eax, SHIFT_4;

		n_1x:
			add ecx, 2;
			movzx eax, ax;
			mov[ebp - 0x14], ecx;

			cmp eax, NO_FONT;
			ja n_2;
			mov eax, NOT_DEF;

		n_2:
			jmp n_5;

		n_3:
			movzx eax, byte ptr[eax + ecx];
		n_5:
			mov edx, [edx + eax * 4 + 0xA4]; // 0x8C -> 0xA4

			push n_4_v30;
			ret;
		}
	}

	uintptr_t n_4_v301;
	__declspec(naked) void n_1_v301()
	{
		__asm {
			cmp byte ptr[eax + ecx], ESCAPE_SEQ_1;
			jz n_10;

			cmp byte ptr[eax + ecx], ESCAPE_SEQ_2;
			jz n_11;

			cmp byte ptr[eax + ecx], ESCAPE_SEQ_3;
			jz n_12;

			cmp byte ptr[eax + ecx], ESCAPE_SEQ_4;
			jz n_13;

			jmp n_3;

		n_10:
			movzx eax, word ptr[eax + ecx + 1];
			jmp n_1x;

		n_11:
			movzx eax, word ptr[eax + ecx + 1];
			sub eax, SHIFT_2;
			jmp n_1x;

		n_12:
			movzx eax, word ptr[eax + ecx + 1];
			add eax, SHIFT_3;
			jmp n_1x;

		n_13:
			movzx eax, word ptr[eax + ecx + 1];
			add eax, SHIFT_4;

		n_1x:
			add ecx, 2;
			movzx eax, ax;
			mov[ebp - 0x1C], ecx; // 変更した

			cmp eax, NO_FONT;
			ja n_2;
			mov eax, NOT_DEF;

		n_2:
			jmp n_5;

		n_3:
			movzx eax, byte ptr[eax + ecx];
		n_5:
			mov esi, [esi + eax * 4 + 0xA4]; 

			push n_4_v301;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func4_hook(RunOptions *options) {
		std::string desc = "func4";

		switch (options->version) {
		case v2_8_X:
			// movzx eax, byte ptr [eax+ecx]
			byte_pattern::temp_instance().find_pattern("0F B6 04 08 8B 94 82 8C");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), n_1_v28);
				// mov [ebp+var_34],edx
				n_4_v28 = byte_pattern::temp_instance().get_first().address(11);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_0:
			// movzx eax, byte ptr [eax+ecx]
			byte_pattern::temp_instance().find_pattern("0F B6 04 08 8B 94 82 A4");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), n_1_v30);
				// mov [ebp+var_34],edx
				n_4_v30 = byte_pattern::temp_instance().get_first().address(11);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_X:
			// movzx eax, byte ptr [eax+ecx]
			byte_pattern::temp_instance().find_pattern("0F B6 04 08 8B B4 86 A4 00 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), n_1_v301);
				// mov [ebp+var_3C],esi
				n_4_v301 = byte_pattern::temp_instance().get_first().address(11);
			}
			else return CK2ERROR1;
			return NOERROR;

		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("map character view");

		/* */
		result |= func1_2_hook(options);

		/* */
		result |= func3_hook(options);

		/* */
		result |= func4_hook(options);

		return result;
	}

}