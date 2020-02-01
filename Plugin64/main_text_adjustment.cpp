#include "pch.h"
#include "plugin_64.h"

// これはwin32のときにMainTextLineBreakだったもの
namespace MainTextAdjustment {
	extern "C" {
		void mainTextAdjustmentProc1();
		void mainTextAdjustmentProc2();
		void mainTextAdjustmentProc3();
		uintptr_t mainTextAdjustmentProc1ReturnAddress;
		uintptr_t mainTextAdjustmentProc2ReturnAddress1;
		uintptr_t mainTextAdjustmentProc2ReturnAddress2;
		uintptr_t mainTextAdjustmentProc3ReturnAddress;
	}

	DllError mainTextAdjustmentProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movzx   eax, byte ptr [rax+rdx]
			BytePattern::temp_instance().find_pattern("0F B6 04 10 4D 8B BC C3 E8 00 00 00");
			if (BytePattern::temp_instance().has_size(1, "文字取得")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz      loc_xxxxx
				mainTextAdjustmentProc1ReturnAddress = address + 0xF;

				Injector::MakeJMP(address, mainTextAdjustmentProc1, true);
			}
			else {
				e.unmatch.mainTextAdjustmentProc1Injector = true;
			}
			break;
		default:
			e.version.mainTextAdjustmentProc1Injector = true;
		}

		return e;
	}
	
	DllError mainTextAdjustmentProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movzx   eax, byte ptr [rax+rdx]
			BytePattern::temp_instance().find_pattern("FF C7 4C 8B 4B 10 41 3B F9");
			if (BytePattern::temp_instance().has_size(1, "カウントアップ")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jmp     loc_xxxxx
				mainTextAdjustmentProc2ReturnAddress1 = address + 0x17;

				// jge     {loc_xxxxx}
				mainTextAdjustmentProc2ReturnAddress2 = Injector::GetBranchDestination(address + 0x9).as_int();

				Injector::MakeJMP(address, mainTextAdjustmentProc2, true);
			}
			else {
				e.unmatch.mainTextAdjustmentProc2Injector = true;
			}
			break;
		default:
			e.version.mainTextAdjustmentProc2Injector = true;
		}

		return e;
	}

	DllError mainTextAdjustmentProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// cmp     cl, 20h
			BytePattern::temp_instance().find_pattern("80 F9 20 44 0F 44 FF");
			if (BytePattern::temp_instance().has_size(1, "文字取得前のスペース(0x20)チェック")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cmp     r8, 10h
				mainTextAdjustmentProc3ReturnAddress = address + 0x15;

				Injector::MakeJMP(address, mainTextAdjustmentProc3, true);
			}
			else {
				e.unmatch.mainTextAdjustmentProc3Injector = true;
			}
			break;
		default:
			e.version.mainTextAdjustmentProc3Injector = true;
		}

		return e;
	}


	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mainTextAdjustmentProc1Injector(options);
		result |= mainTextAdjustmentProc2Injector(options);
		result |= mainTextAdjustmentProc3Injector(options);

		return result;
	}
}