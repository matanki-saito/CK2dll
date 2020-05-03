#include "pch.h"
#include "plugin_64.h"
#include "escape_tool.h"

// 3.3.2時点でSDLのversionは2.0.5で外部DLL化された。
namespace Input {
	extern "C" {
		void inputProc1();
		uintptr_t inputProc1ReturnAddress1;
		uintptr_t inputProc1ReturnAddress2;
		uintptr_t inputProc1CallAddress;

		void inputProc2();
		uintptr_t inputProc2ReturnAddress;
	}

	DllError inputProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movzx   ecx, [rbp+57h+var_6C]
			BytePattern::temp_instance().find_pattern("0F B6 4D EB 41 8B DF 80 F9 80 73 05 0F B6 D9 EB 17");
			if (BytePattern::temp_instance().has_size(1, "入力した文字をutf8からエスケープ列へ変換する")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				inputProc1CallAddress = (uintptr_t)utf8ToEscapedStr3;

				// movsx   eax, cl
				inputProc1ReturnAddress1 = address + 0x28;

				Injector::MakeJMP(address, inputProc1, true);
			}
			else {
				e.unmatch.inputProc1Injector = true;
			}

			// call    qword ptr [rax+18h]
			BytePattern::temp_instance().find_pattern("48 8D 1D D9 C4 3D 00 48 8D 4D DF");
			if (BytePattern::temp_instance().has_size(1, "入力した文字をutf8からエスケープ列へ変換する")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();
				// lea     rbx, off_7FF63B038D38
				inputProc1ReturnAddress2 = address;
			}
			else {
				e.unmatch.inputProc1Injector = true;
			}

			break;
		default:
			e.version.inputProc1Injector = true;
		}

		return e;
	}

	DllError inputProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// mov     rax, [rdi]
			BytePattern::temp_instance().find_pattern("48 8B 07 48 8B CF 85 DB 74 08 FF 90 40 01 00 00");
			if (BytePattern::temp_instance().has_size(1, "バックスペース処理の修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// movzx   r8d, word ptr [rdi+56h]
				inputProc2ReturnAddress = address + 0x18;

				Injector::MakeJMP(address, inputProc2, true);
			}
			else {
				e.unmatch.inputProc2Injector = true;
			}
			break;
		default:
			e.version.inputProc2Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		//result |= inputProc1Injector(options);
		//result |= inputProc2Injector(options);

		return result;
	}
}