#include "stdinc.h"
#include "byte_pattern.h"

namespace Issue32 {

	/*-----------------------------------------------*/

	uintptr_t issue_32_copyBufFunc_v28;
	uintptr_t issue_32_copyBufFunc_v30;

	/*-----------------------------------------------*/

	errno_t copyBufFunc_hook(CK2Version version) {
		std::string desc = "copy buf func";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("8B D9 89 5D EC C7 45 E8 00 00 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				issue_32_copyBufFunc_v28 = byte_pattern::temp_instance().get_first().address(-0x23);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_X:
			// sub esp,38h
			byte_pattern::temp_instance().find_pattern("83 EC 38 53 56 57 8B F9 C7 45 E8");
			if (byte_pattern::temp_instance().has_size(2, desc)) {
				// push ebp
				issue_32_copyBufFunc_v30 = byte_pattern::temp_instance().get_first().address(-0x18);
			}
			else return CK2ERROR1;
			return NOERROR;

		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	char *HOUSE = "HOUSE";
	uintptr_t issue_32_fix1_v28_end;
	__declspec(naked) void issue_32_fix1_v28_start() {
		__asm {
			mov esi, eax;

			mov edx, HOUSE;
			//mov byte ptr[ebp - 0x4], 4;
			lea ecx, [ebp - 0x168];
			call issue_32_copyBufFunc_v28;
			push eax;

			lea ecx, [ebp - 0x78];
			mov byte ptr[ebp - 0x4], 0xA;
			push ecx;
			
			mov eax, esi;

			push issue_32_fix1_v28_end;
			ret;
		}
	}

	uintptr_t issue_32_fix1_v30_end;
	__declspec(naked) void issue_32_fix1_v30_start() {
		__asm {
			mov esi, eax;

			mov edx, HOUSE;
			//mov byte ptr[ebp - 0x4], 4;
			lea ecx, [ebp - 0x74];
			call issue_32_copyBufFunc_v30;
			push eax;

			lea ecx, [ebp - 0xA4];
			mov byte ptr[ebp - 0x4], 0x5;
			push ecx;

			mov eax, esi;

			push issue_32_fix1_v30_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix1_hook(CK2Version version) {
		std::string desc = "fix 1";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("56 8D 4D 88 C6 45 FC 0A 51");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov esi,eax
				// mod edx, offset aHouse ;
				injector::WriteMemory(byte_pattern::temp_instance().get_first().address(-0x47), 0xEB, true);
				injector::WriteMemory(byte_pattern::temp_instance().get_first().address(-0x46), 0x14, true);

				// push esi
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_32_fix1_v28_start);
				// mov ecx, eax
				issue_32_fix1_v28_end = byte_pattern::temp_instance().get_first().address(9);
			}
			else return CK2ERROR1;
			return NOERROR;
		case v3_0_X:
			// この処理は大きなブロックから単一の関数に切り出されるようになった
			// sub esp,0F8h
			byte_pattern::temp_instance().find_pattern("81 EC F8 00 00 00 53 56 57 8B F9 C7 45 D8 0F");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov esi,eax
				// mod edx, offset aHouse ;
				injector::WriteMemory(byte_pattern::temp_instance().get_first().address(0x66), 0xEB, true);
				injector::WriteMemory(byte_pattern::temp_instance().get_first().address(0x67), 0x11, true);

				// push esi
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0xA7), issue_32_fix1_v30_start);
				// mov ecx, eax
				issue_32_fix1_v30_end = byte_pattern::temp_instance().get_first().address(0xA7+0xC);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t issue_32_fix2_v28_end;
	__declspec(naked) void issue_32_fix2_v28_start() {
		__asm {
			mov esi, eax;

			mov edx, HOUSE;
			lea ecx, [ebp - 0x120];
			call issue_32_copyBufFunc_v28;
			push eax;

			lea ecx, [ebp - 0x24];
			mov byte ptr[ebp - 0x4], 0x8;
			push ecx;

			mov eax, esi;

			push issue_32_fix2_v28_end;
			ret;
		}
	}

	uintptr_t issue_32_fix2_v30_end;
	__declspec(naked) void issue_32_fix2_v30_start() {
		__asm {
			mov esi, eax;

			mov edx, HOUSE;
			lea ecx, [ebp - 0x120];
			call issue_32_copyBufFunc_v30;
			push eax;

			lea ecx, [ebp - 0x58];
			mov byte ptr[ebp - 0x4], 0x8;
			push ecx;

			mov eax, esi;

			push issue_32_fix2_v30_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix2_hook(CK2Version version) {
		std::string desc = "fix 2";

		switch (version) {
		case v2_8_X:
			// push esi
			byte_pattern::temp_instance().find_pattern("56 8D 4D DC C6 45 FC 08");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov esi,eax
				// mod edx, offset aHouse ;
				injector::WriteMemory(byte_pattern::temp_instance().get_first().address(-0x41), 0xEB, true);
				injector::WriteMemory(byte_pattern::temp_instance().get_first().address(-0x40), 0x14, true);

				// push esi
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_32_fix2_v28_start);
				// mov ecx, eax
				issue_32_fix2_v28_end = byte_pattern::temp_instance().get_first().address(9);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_X:
			// push esi
			byte_pattern::temp_instance().find_pattern("56 8D 4D A8 C6 45 FC 08 51");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov esi,eax
				// mod edx, offset aHouse ;
				injector::WriteMemory(byte_pattern::temp_instance().get_first().address(-0x44), 0xEB, true);
				injector::WriteMemory(byte_pattern::temp_instance().get_first().address(-0x43), 0x14, true);

				// push esi
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_32_fix2_v30_start);
				// mov ecx, eax
				issue_32_fix2_v30_end = byte_pattern::temp_instance().get_first().address(9);
			}
			else return CK2ERROR1;
			return NOERROR;

		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(CK2Version version) {
		errno_t result = NOERROR;

		/* issue-32 「家 XXX」を「XXX家」にしたい */
		byte_pattern::debug_output2("Fix Issue 32");

		// 関数フック
		result |= copyBufFunc_hook(version);

		// １箇所目。
		// https://github.com/matanki-saito/CK2dll/issues/32#issuecomment-430287085
		result |= fix1_hook(version);

		// ２箇所目
		// https://github.com/matanki-saito/CK2dll/issues/32#issuecomment-430313354
		result |= fix2_hook(version);

		return result;
	}
}