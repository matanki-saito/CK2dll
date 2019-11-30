#include "pch.h"
#include "plugin_64.h"

namespace MapView {
	extern "C" {
		void mapViewProc1();
		void mapViewProc2();
		void mapViewProc3();
		uintptr_t mapViewProc1ReturnAddress;
		uintptr_t mapViewProc2ReturnAddress;
		uintptr_t mapViewProc3ReturnAddress;
		uintptr_t mapViewProc3CallAddress;
	}

	DllError mapViewProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movzx   eax, byte ptr [rax+rsi]
			BytePattern::temp_instance().find_pattern("0F B6 04 30 4C 8B 9C C7 E8 00 00 00");
			if (BytePattern::temp_instance().has_size(1, "処理ループ２の文字取得処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				//  jnz     short loc_xxxxx
				mapViewProc1ReturnAddress = address + 0x0F;

				Injector::MakeJMP(address, mapViewProc1, true);
			}
			else {
				e.unmatch.mapViewProc1Injector = true;
			}
			break;
		default:
			e.version.mapViewProc1Injector = true;
		}

		return e;
	}

	DllError mapViewProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movzx   eax, byte ptr [rax+r12]
			BytePattern::temp_instance().find_pattern("42 0F B6 04 20 48 8B 8D 30 03 00 00");
			if (BytePattern::temp_instance().has_size(1, "処理ループ１の文字取得処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// test    r15, r15
				mapViewProc2ReturnAddress = address + 0x14;

				Injector::MakeJMP(address, mapViewProc2, true);
			}
			else {
				e.unmatch.mapViewProc2Injector = true;
			}
			break;
		default:
			e.version.mapViewProc2Injector = true;
		}

		return e;
	}

	DllError mapViewProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// byte ptr [rbp-8], 0
			BytePattern::temp_instance().find_pattern("C6 45 F8 00 45 0F B6 04 04");
			if (BytePattern::temp_instance().has_size(1, "処理ループ１の文字コピー")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx}
				mapViewProc3CallAddress = Injector::GetBranchDestination(address + 0x12).as_int();

				// nop
				mapViewProc3ReturnAddress = address + 0x17;

				Injector::MakeJMP(address, mapViewProc3, true);
			}
			else {
				e.unmatch.mapViewProc3Injector = true;
			}
			break;
		default:
			e.version.mapViewProc3Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mapViewProc1Injector(options);
		result |= mapViewProc2Injector(options);
		result |= mapViewProc3Injector(options);

		return result;
	}
}