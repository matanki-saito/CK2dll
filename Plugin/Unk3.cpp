#include "stdinc.h"
#include "byte_pattern.h"

namespace Unk3 {
	/*-----------------------------------------------*/

	uintptr_t j_7;
	uintptr_t j_8;
	__declspec(naked) void j_1()
	{
		__asm {
			mov al, [esi + edx];

			cmp al, ESCAPE_SEQ_1;
			jz j_10;

			cmp al, ESCAPE_SEQ_2;
			jz j_11;

			cmp al, ESCAPE_SEQ_3;
			jz j_12;

			cmp al, ESCAPE_SEQ_4;
			jz j_13;

			mov[ebp - 0x2], al;
			movzx eax, al;
			jmp j_6

		j_10:
			movzx eax, word ptr[esi + edx + 1];
			jmp j_2;

		j_11:
			movzx eax, word ptr[esi + edx + 1];
			sub eax, SHIFT_2;
			jmp j_2;

		j_12:
			movzx eax, word ptr[esi + edx + 1];
			add eax, SHIFT_3;
			jmp j_2;

		j_13:
			movzx eax, word ptr[esi + edx + 1];
			add eax, SHIFT_4;
		
		j_2:
			movzx eax, ax;
			cmp eax, NO_FONT;

			ja j_3;
			mov eax, NOT_DEF;

		j_3:
			mov[ebp - 0x2], 0x10;
			add esi, 2;

			cmp esi, ebx;
			jnb j_4;

		j_6:
			mov ecx, [ebp - 0x10];
			push j_7;
			ret;

		j_4:
			mov ecx, [ebp - 0x8];
			push j_8;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix1_hook(RunOptions *options) {
		std::string desc = "fix1";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			byte_pattern::temp_instance().find_pattern("8A 04 16 8B 4D F0 88");
			if (byte_pattern::temp_instance().has_size(1, desc + " start")) {
				// mov al, [esi+edx]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), j_1);
				// mov ecx, [ecx+eax*4+OFFSET]
				j_7 = byte_pattern::temp_instance().get_first().address(12);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("3B F9 0F 4F CF 5F 5E 8B");
			if (byte_pattern::temp_instance().has_size(1, desc + " end2")) {
				// cmp edi,ecx
				j_8 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("unk3");

		//
		result |= fix1_hook(options);

		return result;
	}
}