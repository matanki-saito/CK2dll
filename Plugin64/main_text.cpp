#include "pch.h"
#include "plugin_64.h"

namespace MainText {
	extern "C" {
		void mainTextProc1();
		void mainTextProc2();
		void mainTextProc3();
		void mainTextProc4();
		uintptr_t mainTextProc1ReturnAddress;
		uintptr_t mainTextProc2ReturnAddress;
		uintptr_t mainTextProc2BufferAddress1;
		uintptr_t mainTextProc2BufferAddress2;
		uintptr_t mainTextProc3ReturnAddress1;
		uintptr_t mainTextProc3ReturnAddress2;
		uintptr_t mainTextProc4ReturnAddress;
	}

	DllError mainTextProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movsxd rax, edi
			BytePattern::temp_instance().find_pattern("48 63 C3 42 0F B6 0C 20 4C");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ２の文字取得修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jnz     short loc_xxxxx
				mainTextProc1ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, mainTextProc1, true);
			}
			else {
				e.unmatch.mainTextProc1Injector = true;
			}
			break;
		default:
			e.version.mainTextProc1Injector = true;
		}

		return e;
	}

	DllError mainTextProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movsxd  rax, edi
			BytePattern::temp_instance().find_pattern("48 63 C7 4C 8D 0D ? ? ? ? 42");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１のカウント処理修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz      loc_xxxxx
				mainTextProc2ReturnAddress = address + 0x23;

				// lea r9, {unk_XXXXX}
				mainTextProc2BufferAddress1 = Injector::GetBranchDestination(address + 0x3).as_int();

				// lea r11, {unk_XXXXX}
				mainTextProc2BufferAddress2 = Injector::GetBranchDestination(address + 0x12).as_int();

				Injector::MakeJMP(address, mainTextProc2, true);
			}
			else {
				e.unmatch.mainTextProc2Injector = true;
			}
			break;
		default:
			e.version.mainTextProc2Injector = true;
		}

		return e;
	}

	DllError mainTextProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// cmp cs:byte_xxxxx, 0
			BytePattern::temp_instance().find_pattern("80 3D ? ? ? ? 00 0F 84 3F 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の改行処理の戻り先２取得")) {
				mainTextProc3ReturnAddress2 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.unmatch.mainTextProc3Injector2 = true;
			}

			// cmp     dword ptr [rbp-6Ch], 0
			BytePattern::temp_instance().find_pattern("83 7D 94 00 0F 85 ? ? 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の改行処理を修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				//  jle     loc_xxxxxx
				mainTextProc3ReturnAddress1 = address + 0x11;

				Injector::MakeJMP(address, mainTextProc3, true);
			}
			else {
				e.unmatch.mainTextProc3Injector = true;
			}
			break;
		default:
			e.version.mainTextProc3Injector = true;
		}

		return e;
	}

	DllError mainTextProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movzx   eax, cl
			BytePattern::temp_instance().find_pattern("0F B6 C1 4C 8B 8C C6 E8 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の文字取得修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz loc_xxxxx
				mainTextProc4ReturnAddress = address + 14;

				Injector::MakeJMP(address, mainTextProc4, true);
			}
			else {
				e.unmatch.mainTextProc4Injector = true;
			}
			break;
		default:
			e.version.mainTextProc4Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mainTextProc1Injector(options);
		result |= mainTextProc2Injector(options);
		result |= mainTextProc3Injector(options);
		result |= mainTextProc4Injector(options);

		return result;
	}
}