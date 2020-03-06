#include "pch.h"
#include "plugin_64.h"

namespace DecorativeLetter {
	extern "C" {
		void decorativeLetterProc1();
		void decorativeLetterProc2();
		void decorativeLetterProc3();
		void decorativeLetterProc4();
		void decorativeLetterProc5();
		void decorativeLetterProc6();
		void decorativeLetterProc7();
		uintptr_t decorativeLetterProc1ReturnAddress;
		uintptr_t decorativeLetterProc2CallAddress;
		uintptr_t decorativeLetterProc2ReturnAddress;
		uintptr_t decorativeLetterProc3ReturnAddress;
		uintptr_t decorativeLetterProc4ReturnAddress;
		uintptr_t decorativeLetterProc5ReturnAddress;
		uintptr_t decorativeLetterProc6ReturnAddress;
		uintptr_t decorativeLetterProc7ReturnAddress;
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
			if (BytePattern::temp_instance().has_size(1, "大文字化キャンセル")) {
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


	DllError decorativeLetterProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			//  mov     rbx, rax
			BytePattern::temp_instance().find_pattern("48 8B D8 41 B9 01 00 00 00 45 33 C0");
			if (BytePattern::temp_instance().has_size(3, "切り出し")) {
				uintptr_t address = BytePattern::temp_instance().get(2).address();

				// lea     rcx, [rbp+810h+var_760]
				decorativeLetterProc4ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, decorativeLetterProc4, true);
			}
			else {
				e.unmatch.decorativeLetterProc4Injector = true;
			}
			break;
		default:
			e.version.decorativeLetterProc4Injector = true;
		}

		return e;
	}

	DllError decorativeLetterProc5Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			//  mov     r9d, [rbp+810h+var_750]
			BytePattern::temp_instance().find_pattern("44 8B 8D C0 00 00 00 41 B8 01 00 00 00");
			if (BytePattern::temp_instance().has_size(1, "切り出した残りの部分の処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// lea     rcx, [rbp+810h+var_760]
				decorativeLetterProc5ReturnAddress = address + 0x14;

				Injector::MakeJMP(address, decorativeLetterProc5, true);
			}
			else {
				e.unmatch.decorativeLetterProc5Injector = true;
			}
			break;
		default:
			e.version.decorativeLetterProc5Injector = true;
		}

		return e;
	}

	DllError decorativeLetterProc6Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// mov     rbx, rax
			BytePattern::temp_instance().find_pattern("48 8B D8 41 B9 01 00 00 00");
			if (BytePattern::temp_instance().has_size(2, "切り出し")) {
				uintptr_t address = BytePattern::temp_instance().get_second().address();

				// lea     rcx, [rbp+70h]
				decorativeLetterProc6ReturnAddress = address + 0x10;

				Injector::MakeJMP(address, decorativeLetterProc6, true);
			}
			else {
				e.unmatch.decorativeLetterProc6Injector = true;
			}
			break;
		default:
			e.version.decorativeLetterProc6Injector = true;
		}

		return e;
	}

	DllError decorativeLetterProc7Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// mov     r9d, [rbp+80h]
			BytePattern::temp_instance().find_pattern("44 8B 8D 80 00 00 00 41 B8 01 00 00 00");
			if (BytePattern::temp_instance().has_size(1, "切り出した残りの部分の処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// lea     rcx, [rbp+70h]
				decorativeLetterProc7ReturnAddress = address + 0x14;

				Injector::MakeJMP(address, decorativeLetterProc7, true);
			}
			else {
				e.unmatch.decorativeLetterProc7Injector = true;
			}
			break;
		default:
			e.version.decorativeLetterProc7Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		// 一般ダイアログ
		result |= decorativeLetterProc1Injector(options);
		result |= decorativeLetterProc2Injector(options);
		result |= decorativeLetterProc3Injector(options);

		// 継承ダイアログ（heir）
		result |= decorativeLetterProc4Injector(options);
		result |= decorativeLetterProc5Injector(options);

		// 継承ダイアログ（dead）
		result |= decorativeLetterProc6Injector(options);
		result |= decorativeLetterProc7Injector(options);

		return result;
	}
}