#include "stdinc.h"
#include "byte_pattern.h"


namespace MapAdj
{
	/*-----------------------------------------------*/

	uintptr_t p_5;
	__declspec(naked) void p_1()
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

			push p_5;
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

			push p_5;
			ret;
		}
	}

	uintptr_t q_4;
	__declspec(naked) void q_1()
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

			push q_4;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func1_2_hook(CK2Version version) {
		std::string desc = "func1,2";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("8A 04 18 8D 8D 04 FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), p_1);
				p_5 = byte_pattern::temp_instance().get_first().address(12);
	
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x14), q_1);
				q_4 = byte_pattern::temp_instance().get_first().address(0x19);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t o_5;
	__declspec(naked) void o_1()
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

			push o_5;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func3_hook(CK2Version version) {
		std::string desc = "func3";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("0F B6 04 18 8B 55 E0");
			if (byte_pattern::temp_instance().has_size(1,desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), o_1);
				o_5 = byte_pattern::temp_instance().get_first().address(7);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t n_4;
	__declspec(naked) void n_1()
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

			push n_4;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func4_hook(CK2Version version) {
		std::string desc = "func4";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("0F B6 04 08 8B 94 82 8C");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), n_1);
				n_4 = byte_pattern::temp_instance().get_first().address(11);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(CK2Version version) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("map adj");

		/* */
		result |= func1_2_hook(version);

		/* */
		result |= func3_hook(version);

		/* */
		result |= func4_hook(version);

		return result;
	}

}