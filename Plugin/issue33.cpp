#include "stdinc.h"
#include "byte_pattern.h"

// https://github.com/matanki-saito/CK2dll/issues/33
namespace Issue33 {

	/*-----------------------------------------------*/

	uintptr_t issue_33_v28_copyBuffFunc;
	
	/*-----------------------------------------------*/

	errno_t func_hook(RunOptions *options) {
		std::string desc = "func hook";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
			/* コピー関数 */
			byte_pattern::temp_instance().find_pattern("83 EC 20 56 FF 75 0C 8D 45 D8");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// sub esp,20h
				issue_33_v28_copyBuffFunc = byte_pattern::temp_instance().get_first().address(-0x18);
			}
			else return CK2ERROR1;

			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t issue_33_v28_end;
	__declspec(naked) void issue_33_v28_start() {
		__asm {
			//§! → LOYAL_TO
			push eax;
			mov byte ptr[ebp - 0x4], 0x43;
			lea ecx,[ebp - 0xB8]; // buf
			push ecx;
			lea ecx, [ebp - 0xA0]; // §!
			call issue_33_v28_copyBuffFunc;

			// XXX → §!LOYAL_TO
			push eax;
			mov byte ptr[ebp - 0x4], 0x44;
			lea ecx, [ebp - 0xF0]; // buf
			push ecx;
			mov ecx, esi;
			call issue_33_v28_copyBuffFunc;

			//§Y → XXX§!LOYAL_TO
			push eax;
			mov byte ptr[ebp - 0x4], 0x45;
			lea ecx, [ebp - 0x10C]; // buf
			push ecx;
			lea ecx, [ebp - 0xD0]; // §Y
			call issue_33_v28_copyBuffFunc;

			push issue_33_v28_end;
			ret;
		}
	}

	uintptr_t issue_33_v30_end;
	__declspec(naked) void issue_33_v30_start() {
		__asm {
			//§! → LOYAL_TO
			push eax;
			mov byte ptr[ebp - 0x4], 0x43;
			lea ecx, [ebp - 0xBC]; // buf
			push ecx;
			lea ecx, [ebp - 0xA4]; // §!
			call issue_33_v28_copyBuffFunc;

			// XXX → §!LOYAL_TO
			push eax;
			mov byte ptr[ebp - 0x4], 0x44;
			lea ecx, [ebp - 0xF4]; // buf
			push ecx;
			mov ecx, esi;
			call issue_33_v28_copyBuffFunc;

			//§Y → XXX§!LOYAL_TO
			push eax;
			mov byte ptr[ebp - 0x4], 0x45;
			lea ecx, [ebp - 0x10C]; // buf
			push ecx;
			lea ecx, [ebp - 0xD4]; // §Y
			call issue_33_v28_copyBuffFunc;

			push issue_33_v30_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix1_hook(RunOptions *options) {
		std::string desc = "fix 1";

		switch (options->version) {
		case v2_8_X:
			/* issue-33 「に忠誠を誓っている 王 ロスラン」を「王 ロスランに忠誠を誓っているにする」 */
			byte_pattern::temp_instance().find_pattern("8D 8D 30 FF FF FF C6 45 FC 43 51 8D 8D");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// lea ecx, [ebp+var_D0]
				// mov byte ptr [ebp+var_4],43h
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_33_v28_start);
				// mov ecx, [ebp+arg_0]
				issue_33_v28_end = byte_pattern::temp_instance().get_first().address(0x45);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
			/* issue-33 「に忠誠を誓っている 王 ロスラン」を「王 ロスランに忠誠を誓っているにする」 */
			byte_pattern::temp_instance().find_pattern("8D 8D 2C FF FF FF C6 45 FC 43");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// lea ecx, [ebp+var_D0]
				// mov byte ptr [ebp+var_4],43h
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_33_v30_start);
				// mov ecx, [ebp+arg_0]
				issue_33_v30_end = byte_pattern::temp_instance().get_first().address(0x45);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("Fix Issue 33");

		result |= func_hook(options);

		result |= fix1_hook(options);

		return result;
	}
}