#include "stdinc.h"
#include "byte_pattern.h"

namespace DecorativeLetterEndDialog
{
	/*-----------------------------------------------*/
	
	uintptr_t aa_5;
	__declspec(naked) void aa_1()
	{
		__asm {
			mov esi, eax;
			lea ecx, [ebp - 0xD4];
			mov eax, ecx;
			cmp dword ptr[eax + 0x14], 0x10;
			jb aa_2;
			mov eax, [eax];

		aa_2:
			mov al, [eax];
			cmp al, ESCAPE_SEQ_1;
			jz aa_3;

			cmp al, ESCAPE_SEQ_2;
			jz aa_3;
			
			cmp al, ESCAPE_SEQ_3;
			jz aa_3;

			cmp al, ESCAPE_SEQ_4;
			jz aa_3;

			jmp aa_4;

		aa_3:
			push 3;
			jmp aa_6;

		aa_4:
			push 1;

		aa_6:
			push aa_5;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func1A_hook(RunOptions *options) {
		std::string desc = "func1_A";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			byte_pattern::temp_instance().find_pattern("6A 01 8B F0 8D 8D 2C");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), aa_1);
				aa_5 = byte_pattern::temp_instance().get_first().address(10);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t bb_6;
	__declspec(naked) void bb_1()
	{
		__asm {
			lea ecx, [ebp - 0xD4];
			cmp dword ptr[ecx + 0x14], 0x10;
			jb bb_2;
			mov ecx, [ecx];

		bb_2:
			mov cl, [ecx];

			cmp cl, ESCAPE_SEQ_1;
			jz bb_3;

			cmp cl, ESCAPE_SEQ_2;
			jz bb_3;

			cmp cl, ESCAPE_SEQ_3;
			jz bb_3;

			cmp cl, ESCAPE_SEQ_4;
			jz bb_3;

			jmp bb_4;

		bb_3:
			push 3;
			jmp bb_5;

		bb_4:
			push 1;

		bb_5:
			push eax;
			lea ecx, [ebp - 0xD4];

			push bb_6;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func1B_hook(RunOptions *options) {
		std::string desc = "func1_B";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			byte_pattern::temp_instance().find_pattern("E8 ? ? ? ? FF B5 3C FF FF FF 8D 45");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0xE), bb_1);
				bb_6 = byte_pattern::temp_instance().get_first().address(0x17);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t ll_5_v28;
	__declspec(naked) void ll_1_v28()
	{
		__asm {
			lea ecx, [ebp - 0x88];
			mov eax, ecx;
			cmp dword ptr[eax + 0x14], 0x10;
			jb ll_4;
			mov eax, [eax];
		
		ll_4:
			mov al, [eax];
			
			cmp al, ESCAPE_SEQ_1;
			jz ll_3;

			cmp al, ESCAPE_SEQ_2;
			jz ll_3;

			cmp al, ESCAPE_SEQ_3;
			jz ll_3;

			cmp al, ESCAPE_SEQ_4;
			jz ll_3;

			push 1;
			jmp ll_2;

		ll_3:
			push 3;

		ll_2:
			lea eax, [ebp - 0x168];
			push 0;

			push ll_5_v28;
			ret;
		}
	}

	uintptr_t ll_5_v30;
	__declspec(naked) void ll_1_v30()
	{
		__asm {
			lea ecx, [ebp - 0x8C]; // 変更された
			mov eax, ecx;
			cmp dword ptr[eax + 0x14], 0x10;
			jb ll_4;
			mov eax, [eax];

		ll_4:
			mov al, [eax];

			cmp al, ESCAPE_SEQ_1;
			jz ll_3;

			cmp al, ESCAPE_SEQ_2;
			jz ll_3;

			cmp al, ESCAPE_SEQ_3;
			jz ll_3;

			cmp al, ESCAPE_SEQ_4;
			jz ll_3;

			push 1;
			jmp ll_2;

		ll_3:
			push 3;

		ll_2:
			lea eax, [ebp - 0x16C]; // 変更された
			push 0;

			push ll_5_v30;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func2A_hook(RunOptions *options) {
		std::string desc = "func2_A";

		switch (options->version) {
		case v2_8_X:
			// push 1
			byte_pattern::temp_instance().find_pattern("6A 01 6A 00 8D 85 98");
			if (byte_pattern::temp_instance().has_size(1,desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), ll_1_v28);
				ll_5_v28 = byte_pattern::temp_instance().get_first().address(10);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_0:
		case v3_0_X:
			// push 1
			byte_pattern::temp_instance().find_pattern("6A 01 6A 00 8D 85 94 FE FF FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), ll_1_v30);
				ll_5_v30 = byte_pattern::temp_instance().get_first().address(10);
			}
			else return CK2ERROR1;
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t mm_5_v28;
	__declspec(naked) void mm_1_v28()
	{
		__asm {
			lea ecx, [ebp - 0x88];
			cmp dword ptr[ecx + 0x14], 0x10;
			jb mm_3;
			mov ecx, [ecx];

		mm_3:
			mov cl, [ecx];
			cmp cl, ESCAPE_SEQ_1;
			jz mm_2;

			cmp cl, ESCAPE_SEQ_2;
			jz mm_2;

			cmp cl, ESCAPE_SEQ_3;
			jz mm_2;

			cmp cl, ESCAPE_SEQ_4;
			jz mm_2;

			push 1;
			jmp mm_4;

		mm_2:
			push 3;

		mm_4:
			push eax;
			lea ecx, [ebp - 0x88];

			push mm_5_v28;
			ret;
		}
	}

	uintptr_t mm_5_v30;
	__declspec(naked) void mm_1_v30()
	{
		__asm {
			lea ecx, [ebp - 0x8C];
			cmp dword ptr[ecx + 0x14], 0x10;
			jb mm_3;
			mov ecx, [ecx];

		mm_3:
			mov cl, [ecx];
			cmp cl, ESCAPE_SEQ_1;
			jz mm_2;

			cmp cl, ESCAPE_SEQ_2;
			jz mm_2;

			cmp cl, ESCAPE_SEQ_3;
			jz mm_2;

			cmp cl, ESCAPE_SEQ_4;
			jz mm_2;

			push 1;
			jmp mm_4;

		mm_2:
			push 3;

		mm_4:
			push eax;
			lea ecx, [ebp - 0x8C];

			push mm_5_v30;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func2B_hook(RunOptions *options) {
		std::string desc = "func2_B";

		switch (options->version) {
		case v2_8_X:
			// push 1
			byte_pattern::temp_instance().find_pattern("6A 01 50 8D 8D 78 FF FF FF E8");
			if (byte_pattern::temp_instance().has_size(1,desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), mm_1_v28);
				mm_5_v28 = byte_pattern::temp_instance().get_first().address(9);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_0:
		case v3_0_X:
			//lea ecx, [ebp+var_200]
			byte_pattern::temp_instance().find_pattern("8D 85 00 FE FF FF 6A 01 50 8D 8D 74 FF FF FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x6), mm_1_v30);
				mm_5_v30 = byte_pattern::temp_instance().get_first().address(0x6 + 9);
			}
			else return CK2ERROR1;
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("decorative letter end dialog");

		// 1A
		result |= func1A_hook(options);
		// 1B
		result |= func1B_hook(options);
		// 2A
		result |= func2A_hook(options);
		// 2B
		result |= func2B_hook(options);

		return result;
	}

}
