#include "stdinc.h"
#include "byte_pattern.h"

namespace DecorativeLetterInheritDialog
{
	/*-----------------------------------------------*/

	uintptr_t ff_5;
	__declspec(naked) void ff_1()
	{
		__asm {
			mov edi, eax;
			lea ecx, [ebp - 0x34];
			mov eax, ecx;
			cmp dword ptr[eax + 0x14], 0x10;
			jb ff_2;
			mov eax, [eax];

		ff_2:
			mov al, [eax];

			cmp al, ESCAPE_SEQ_1;
			jz ff_3;

			cmp al, ESCAPE_SEQ_2;
			jz ff_3;

			cmp al, ESCAPE_SEQ_3;
			jz ff_3;

			cmp al, ESCAPE_SEQ_4;
			jz ff_3;

			push 1;
			jmp ff_4;

		ff_3:
			push 3;

		ff_4:
			push ff_5;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func1A_hook(CK2Version version) {
		std::string desc = "func1A";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("6A 01 8B F8 8D 4D CC");
			if (byte_pattern::temp_instance().has_size(1,desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), ff_1);
				ff_5 = byte_pattern::temp_instance().get_first().address(7);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t gg_4;
	__declspec(naked) void gg_1()
	{
		__asm {
			lea ecx, [ebp - 0x34];
			cmp dword ptr[ecx + 0x14], 0x10;
			jb gg_2;
			mov ecx, [ecx];

		gg_2:
			mov cl, [ecx];
			cmp cl, ESCAPE_SEQ_1;
			jz gg_3;

			cmp cl, ESCAPE_SEQ_2;
			jz gg_3;

			cmp cl, ESCAPE_SEQ_3;
			jz gg_3;

			cmp cl, ESCAPE_SEQ_4;
			jz gg_3;

			push 1;
			jmp gg_5;

		gg_3:
			push 3;

		gg_5:
			push eax;
			lea ecx, [ebp - 0x34];

			push gg_4;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func1B_hook(CK2Version version) {
		std::string desc = "func1B";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("6A 01 50 8D 4D CC E8");
			if (byte_pattern::temp_instance().has_size(1,desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), gg_1);
				gg_4 = byte_pattern::temp_instance().get_first().address(6);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t hh_6;
	__declspec(naked) void hh_1()
	{
		__asm {
			mov edi, eax;
			lea ecx, [ebp - 0x70];
			mov eax, ecx;
			cmp dword ptr[eax + 0x14], 0x10;
			jb hh_2;
			mov eax, [eax];

		hh_2:
			mov al, [eax];
			cmp al, ESCAPE_SEQ_1;
			jz hh_3;

			cmp al, ESCAPE_SEQ_2;
			jz hh_3;

			cmp al, ESCAPE_SEQ_3;
			jz hh_3;

			cmp al, ESCAPE_SEQ_4;
			jz hh_3;

			push 1;
			jmp hh_4;

		hh_3:
			push 3;

		hh_4:
			push hh_6;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func2A_hook(CK2Version version) {
		std::string desc = "func2A";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("6A 01 8B F8 8D 4D 90 6A");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), hh_1);
				hh_6 = byte_pattern::temp_instance().get_first().address(7);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t ii_5;
	__declspec(naked) void ii_1()
	{
		__asm {
			lea ecx, [ebp - 0x70];
			cmp dword ptr[ecx + 0x14], 0x10;
			jb ii_2;
			mov ecx, [ecx];

		ii_2:
			mov cl, [ecx];
			cmp cl, ESCAPE_SEQ_1;
			jz ii_3;

			cmp cl, ESCAPE_SEQ_2;
			jz ii_3;

			cmp cl, ESCAPE_SEQ_3;
			jz ii_3;

			cmp cl, ESCAPE_SEQ_4;
			jz ii_3;

			push 1;
			jmp ii_4;

		ii_3:
			push 3;

		ii_4:
			push eax;
			lea ecx, [ebp - 0x70];

			push ii_5;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func2B_hook(CK2Version version) {
		std::string desc = "func2B";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("6A 01 50 8D 4D 90 E8");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), ii_1);
				ii_5 = byte_pattern::temp_instance().get_first().address(6);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(CK2Version version) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("map font view");

		// 1A
		result |= func1A_hook(version);
		// 1B
		result |= func1B_hook(version);
		// 2A
		result |= func2A_hook(version);
		// 2B
		result |= func2B_hook(version);

		return result;
	}
}