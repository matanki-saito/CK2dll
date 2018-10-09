#include "stdinc.h"
#include "byte_pattern.h"

namespace Unk2 {
	/*-----------------------------------------------*/

	uintptr_t u_4;
	uintptr_t u_2;
	__declspec(naked) void u_1()
	{
		__asm {
			mov al, [edi + esi];

			cmp al, ESCAPE_SEQ_1;
			jz u_3;

			cmp al, ESCAPE_SEQ_2;
			jz u_3;

			cmp al, ESCAPE_SEQ_3;
			jz u_3;

			cmp al, ESCAPE_SEQ_4;
			jz u_3;

			cmp al, 0xFE;
			
			push u_4;
			ret;

		u_3:
			add esi, 3;
			
			push u_2;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix1_hook(CK2Version version) {
		std::string desc = "fix1";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("83 FB 01 72 34 56 33 F6");
			if (byte_pattern::temp_instance().has_size(1, desc + " start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x15), u_1);
				u_4 = byte_pattern::temp_instance().get_first().address(0x1A);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("80 3C 37 00 75 D9 5E 5F");
			if (byte_pattern::temp_instance().has_size(1, desc + " end2")) {
				u_2 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	/* */
	uintptr_t v_4;
	uintptr_t v_1;
	__declspec(naked) void v_2()
	{
		__asm {
			mov al, [edi + esi];

			cmp al, ESCAPE_SEQ_1;
			jz v_3;

			cmp al, ESCAPE_SEQ_2;
			jz v_3;

			cmp al, ESCAPE_SEQ_3;
			jz v_3;

			cmp al, ESCAPE_SEQ_4;
			jz v_3;

			push v_4;
			ret;

		v_3:
			add esi, 3;

			push v_1;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix2_hook(CK2Version version) {
		std::string desc = "fix2";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("33 F6 80 3F 00 74 28 83 FE 01");
			if (byte_pattern::temp_instance().has_size(1,desc +" start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0xC), v_2);
				v_4 = byte_pattern::temp_instance().get_first().address(0x11);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("80 3C 37 00 75 D8 5F 5E");
			if (byte_pattern::temp_instance().has_size(1,desc +" end")) {
				v_1 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(CK2Version version) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("unk2");

		//
		result |= fix1_hook(version);
		//
		result |= fix2_hook(version);

		return result;
	}
}