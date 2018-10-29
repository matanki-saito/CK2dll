#include "stdinc.h"
#include "byte_pattern.h"

namespace Issue38 {

	/*-----------------------------------------------*/

	uintptr_t issue_38_copyBufFunc_v28;

	/*-----------------------------------------------*/

	errno_t copyBufFunc_hook(CK2Version version) {
		std::string desc = "copy buf func";

		switch (version) {
		case v2_8_X:
			// issue33と同じもの
			// sub esp,20h
			byte_pattern::temp_instance().find_pattern("83 EC 20 56 FF 75 0C 8D 45 D8");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				issue_38_copyBufFunc_v28 = byte_pattern::temp_instance().get_first().address(-0x18);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	union T {
		char text[0x10];
		char* p;
	};

	typedef struct V {
		union T t;
		int len;
		int len2;
	} Vs;

	V *year;
	V *day;

	uintptr_t issue_38_fix1_v28_end;
	__declspec(naked) void issue_38_fix1_v28_start() {
		__asm {
			// edi: year
			// [ebp - 0x44] : _,
			// [ebp - 0x100] : month
			// [ebp - 0x2C] : _
			// [ebp - 0xC0] : day

			//
			mov byte ptr[ebp - 0x4], 8;
			push year;
			lea ecx, [ebp - 0xA8];
			push ecx; // buf
			mov ecx, edi;
			call issue_38_copyBufFunc_v28; 

			//
			lea ecx,[ebp - 0x100];
			mov byte ptr[ebp - 0x4], 9;
			push ecx;
			lea ecx, [ebp - 0x90];
			push ecx; // buf
			mov ecx, eax;
			call issue_38_copyBufFunc_v28;

			//
			lea ecx, [ebp - 0xC0];
			mov byte ptr[ebp - 0x4], 0xA;
			push ecx;
			lea ecx, [ebp - 0x78];
			push ecx; // buf
			mov ecx, eax;
			call issue_38_copyBufFunc_v28;

			//
			push day;
			lea ecx, [ebp - 0x60];
			mov byte ptr[ebp - 0x4], 0Bh;
			push ecx; // buf
			mov ecx, eax;
			call issue_38_copyBufFunc_v28;

			push issue_38_fix1_v28_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix1_hook(CK2Version version) {
		std::string desc = "fix 1";

		year = new V();
		year->t.text[0] = 15;
		year->t.text[1] = '\0';
		year->len = 1;
		year->len2 = 1;

		day = new V();
		day->t.text[0] = 14;
		day->t.text[1] = '\0';
		day->len = 1;
		day->len2 = 1;

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("8D 4D D4 C6 45 FC 08 51 8D 8D 58");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// lea ecx,[ebp+var_2C]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_38_fix1_v28_start);
				// mov byte ptr [ebp+var_4],0Ch
				issue_38_fix1_v28_end = byte_pattern::temp_instance().get_first().address(0x52);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(CK2Version version) {
		errno_t result = NOERROR;

		/* issue-32  「DD MON, YYYY」を「YYYY年MONDD日」にしたい */
		byte_pattern::debug_output2("Fix Issue 38");

		// 関数フック
		result |= copyBufFunc_hook(version);

		result |= fix1_hook(version);

		return result;
	}
}