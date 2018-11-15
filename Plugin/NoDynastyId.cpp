#include "stdinc.h"
#include "byte_pattern.h"

namespace NoDynastyId
{
	/*-----------------------------------------------*/

	uintptr_t issue_suffix_id_r;
	uintptr_t loc_8858F2;
	__declspec(naked) void issue_suffix_id() {
		__asm {
			mov edx, [ebp - 0x18];
			mov esi, [ebp - 0x2C];

			cmp ecx, 3;
			jl issue_suffix_id_ret;

			cmp edx, 0x10;
			lea eax, [ebp - 0x2C];
			cmovnb eax, esi;

			cmp byte ptr[ecx + eax - 3], 0x10;
			jz issue_suffix_id_fix;
			cmp byte ptr[ecx + eax - 3], 0x11;
			jz issue_suffix_id_fix;
			cmp byte ptr[ecx + eax - 3], 0x12;
			jz issue_suffix_id_fix;
			cmp byte ptr[ecx + eax - 3], 0x13;
			jz issue_suffix_id_fix;

			jmp issue_suffix_id_ret;

		issue_suffix_id_fix:
			push loc_8858F2;
			ret;

		issue_suffix_id_ret:

			push issue_suffix_id_r;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix_hook(CK2Version version) {
		std::string desc = "func1";

		switch (version) {
		case v2_8_X:
		case v3_0_X:
			byte_pattern::temp_instance().find_pattern("8B 55 E8 8B 75 D4 83 F9");
			if (byte_pattern::temp_instance().has_size(1, desc + " start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_suffix_id);
				issue_suffix_id_r = byte_pattern::temp_instance().get_first().address(0x06);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("8B 75 C0 8D 45 D4 50 8B");
			if (byte_pattern::temp_instance().has_size(2,desc + " end2")) {
				loc_8858F2 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(CK2Version version) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("no dynasty -id");

		/* dynasty‚É-id‚ª‚Â‚¢‚Ä‚µ‚Ü‚¤–â‘è */
		result |= fix_hook(version);

		return result;
	}

}