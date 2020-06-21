#include "pch.h"
#include "plugin_64.h"

namespace MapAdjustment {
	extern "C" {
		void mapAdjustmentProc1();
		void mapAdjustmentProc2();
		void mapAdjustmentProc3();
		void mapAdjustmentProc4();
		void mapAdjustmentProc5();
		uintptr_t mapAdjustmentProc1ReturnAddress;
		uintptr_t mapAdjustmentProc1CallAddress;
		uintptr_t mapAdjustmentProc2ReturnAddress;
		uintptr_t mapAdjustmentProc3ReturnAddress1;
		uintptr_t mapAdjustmentProc3ReturnAddress2;
		uintptr_t mapAdjustmentProc4ReturnAddress;
		uintptr_t mapAdjustmentProc5ReturnAddress;
	}

	// これはwin32のときはMapAdjにあったが統合した。
	// この処理はwin32のときは独立したprocであったが、win64ではinline展開されている。
	DllError mapAdjustmentProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movsx ecx, byte ptr [rdi + rbx]
			BytePattern::temp_instance().find_pattern("0F B6 04 1F 3C FE 75 06 C6 04 1F DE");
			if (BytePattern::temp_instance().has_size(1, u8"マップ文字の大文字化キャンセル")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx}
				mapAdjustmentProc1CallAddress = Injector::GetBranchDestination(address + 0x11).as_int();

				// jnz	short loc_xxxxx
				mapAdjustmentProc1ReturnAddress = address + 0x21;

				Injector::MakeJMP(address, mapAdjustmentProc1, true);
			}
			else {
				e.unmatch.mapAdjustmentProc1Injector = true;
			}
			break;
		default:
			e.version.mapAdjustmentProc1Injector = true;
		}

		return e;
	}

	DllError mapAdjustmentProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// lea     rax, [rbp+220h+var_218]
			BytePattern::temp_instance().find_pattern("48 8D 45 08 49 83 C8 FF 90 49 FF C0");
			if (BytePattern::temp_instance().has_size(1, u8"文字チェック修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// lea     rdx, [rbp+220h+var_218]
				mapAdjustmentProc2ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, mapAdjustmentProc2, true);
			}
			else {
				e.unmatch.mapAdjustmentProc2Injector = true;
			}
			break;
		default:
			e.version.mapAdjustmentProc2Injector = true;
		}

		return e;
	}

	DllError mapAdjustmentProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// r9, 0FFFFFFFFFFFFFFFFh
			BytePattern::temp_instance().find_pattern("49 83 C9 FF 45 33 C0 48 8D 95 E8 00 00 00 48 8D 4D 60");
			if (BytePattern::temp_instance().has_size(1, u8"文字チェックの後のコピー処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call    sub_xxxxx
				mapAdjustmentProc3ReturnAddress1 = address + 0x12;

				Injector::MakeJMP(address, mapAdjustmentProc3, true);
			}
			else {
				e.unmatch.mapAdjustmentProc3Injector = true;
			}

			// mov     rax, [r15]
			BytePattern::temp_instance().find_pattern("49 8B 07 48 8D 4D 00 48 89 4C 24 28 48 8D 8D 28 01 00 00");
			if (BytePattern::temp_instance().has_size(2, u8"文字チェックの後のコピー処理の戻り先２")) {
				mapAdjustmentProc3ReturnAddress2 = BytePattern::temp_instance().get_second().address();
			}
			else {
				e.unmatch.mapAdjustmentProc3Injector = true;
			}
			break;
		default:
			e.version.mapAdjustmentProc3Injector = true;
		}

		return e;
	}

	DllError mapAdjustmentProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			//  lea     rax, [rbp+220h+var_1A0]
			BytePattern::temp_instance().find_pattern("48 8D 85 80 00 00 00 49 83 FA 10 49 0F 43 C3");
			if (BytePattern::temp_instance().has_size(1, u8"文字取得処理修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// mov     rdx, [rsi+rax*8]
				mapAdjustmentProc4ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, mapAdjustmentProc4, true);
			}
			else {
				e.unmatch.mapAdjustmentProc4Injector = true;
			}
			break;
		default:
			e.version.mapAdjustmentProc4Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mapAdjustmentProc1Injector(options);
		result |= mapAdjustmentProc2Injector(options);
		result |= mapAdjustmentProc3Injector(options);
		result |= mapAdjustmentProc4Injector(options);

		return result;
	}
}