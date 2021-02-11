#include "pch.h"
#include "plugin_64.h"

namespace MainTextOverflow {
	extern "C" {
		void mainTextOverflowProc1();
		void mainTextOverflowProc1v3332();
		void mainTextOverflowProc2();
		void mainTextOverflowProc3();
		uintptr_t mainTextOverflowProc1ReturnAddress;
		uintptr_t mainTextOverflowProc2ReturnAddress1;
		uintptr_t mainTextOverflowProc2ReturnAddress2;
		uintptr_t mainTextOverflowProc3ReturnAddress1;
		uintptr_t mainTextOverflowProc3ReturnAddress2;
	}

	DllError mainTextOverflowProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movzx   eax, byte ptr [rax+rsi]
			BytePattern::temp_instance().find_pattern("0F B6 04 30 4D 8B 94 C5 E8 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"文字取得処理 v3.3.3.2")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz      loc_xxxxx
				mainTextOverflowProc1ReturnAddress = address + 0x0F;

				Injector::MakeJMP(address, mainTextOverflowProc1v3332, true);
			}
			else {
				// movzx   eax, byte ptr [rax+rdi]
				BytePattern::temp_instance().find_pattern("0F B6 04 38 4D 8B 94 C5 E8 00 00 00");
				if (BytePattern::temp_instance().has_size(1, u8"文字取得処理 v3.3.3.[0-1]")) {
					uintptr_t address = BytePattern::temp_instance().get_first().address();

					// jz      loc_xxxxx
					mainTextOverflowProc1ReturnAddress = address + 0x0F;

					Injector::MakeJMP(address, mainTextOverflowProc1, true);
				}
				else {
					e.unmatch.mainTextOverflowProc1Injector = true;
				}
			}
			break;
		default:
			e.version.mainTextOverflowProc1Injector = true;
		}

		return e;
	}

	DllError mainTextOverflowProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movzx   eax, byte ptr [rax+rdi]
			BytePattern::temp_instance().find_pattern("8B 53 10 FF C7 3B FA 0F 8D FB 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"カウントアップ")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jge loc {xxxxx}
				mainTextOverflowProc2ReturnAddress1 = Injector::GetBranchDestination(address + 7).as_int();

				// jmp loc_xxxxx
				mainTextOverflowProc2ReturnAddress2 = address + 0x1D;

				Injector::MakeJMP(address, mainTextOverflowProc2, true);
			}
			else {
				e.unmatch.mainTextOverflowProc1Injector = true;
			}
			break;
		default:
			e.version.mainTextOverflowProc1Injector = true;
		}

		return e;
	}


	DllError mainTextOverflowProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movzx   eax, byte ptr [rax+rdi]
			BytePattern::temp_instance().find_pattern("8D 47 FD C6 04 10 2E 49 83 7F 18 10 72 05 49 8B");
			if (BytePattern::temp_instance().has_size(1, u8"カウントアップ")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jmp loc_xxxxx
				mainTextOverflowProc3ReturnAddress1 = address + 0x13;

				mainTextOverflowProc3ReturnAddress2 = address + 0x16;

				Injector::MakeJMP(address, mainTextOverflowProc3, true);
			}
			else {
				e.unmatch.mainTextOverflowProc1Injector = true;
			}
			break;
		default:
			e.version.mainTextOverflowProc1Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mainTextOverflowProc1Injector(options);
		result |= mainTextOverflowProc2Injector(options);
		result |= mainTextOverflowProc3Injector(options);

		return result;
	}
}