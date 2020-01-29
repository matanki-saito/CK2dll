#include "pch.h"
#include "plugin_64.h"

namespace DecorativeLetter {
	extern "C" {
		void decorativeLetterProc1();
		void decorativeLetterProc2();
		void decorativeLetterProc3();
		uintptr_t decorativeLetterProc1ReturnAddress;
		uintptr_t decorativeLetterProc2CallAddress;
		uintptr_t decorativeLetterProc2ReturnAddress;
		uintptr_t decorativeLetterProc3ReturnAddress;
	}

	DllError decorativeLetterProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// mov     r9d, 1
			BytePattern::temp_instance().find_pattern("41 B9 01 00 00 00 45 33 C0 48 8D 95 30 12 00 00");
			if (BytePattern::temp_instance().has_size(1, "切り出し")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call    sub_140D5FDF0
				decorativeLetterProc1ReturnAddress = address + 0x17;

				Injector::MakeJMP(address, decorativeLetterProc1, true);
			}
			else {
				e.unmatch.decorativeLetterProc1Injector = true;
			}
			break;
		default:
			e.version.decorativeLetterProc1Injector = true;
		}

		return e;
	}

	// 大文字化の処理がinline化されたので、別procにある修正が必要になった
	DllError decorativeLetterProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// lea     rsi, [rax+rdi]
			BytePattern::temp_instance().find_pattern("48 8D 34 38 0F B6 04 38");
			if (BytePattern::temp_instance().has_size(1, "ダイアログ")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx}
				decorativeLetterProc2CallAddress = Injector::GetBranchDestination(address + 0x14).as_int();

				// jnz	short loc_xxxxx
				decorativeLetterProc2ReturnAddress = address + 0x23;

				Injector::MakeJMP(address, decorativeLetterProc2, true);
			}
			else {
				e.unmatch.decorativeLetterProc2Injector = true;
			}
			break;
		default:
			e.version.decorativeLetterProc2Injector = true;
		}

		return e;
	}

	DllError decorativeLetterProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// mov     rbx, rax
			BytePattern::temp_instance().find_pattern("48 8B D8 44 8B 8D E8 02 00 00");
			if (BytePattern::temp_instance().has_size(1, "切り出した残りの部分の処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jnz	short loc_xxxxx
				decorativeLetterProc3ReturnAddress = address + 0x1E;

				Injector::MakeJMP(address, decorativeLetterProc3, true);
			}
			else {
				e.unmatch.decorativeLetterProc3Injector = true;
			}
			break;
		default:
			e.version.decorativeLetterProc3Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= decorativeLetterProc1Injector(options);
		result |= decorativeLetterProc2Injector(options);
		result |= decorativeLetterProc3Injector(options);

		return result;
	}
}