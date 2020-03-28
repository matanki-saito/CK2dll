#include "pch.h"
#include "plugin_64.h"
#include "escape_tool.h"

namespace FileName {
	extern "C" {
		void fileNameProc1();
		void fileNameProc2();

		uintptr_t fileNameProc1ReturnAddress;
		uintptr_t fileNameProc2CallAddress;
		uintptr_t fileNameProcEscapedStrToUtf8;
		uintptr_t fileNameProcReplaceTextObject;
		uintptr_t fileNameProc2ReturnAddress;
	}

	DllError fileNameProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movsxd  r10, dword ptr [rcx+10h]
			BytePattern::temp_instance().find_pattern("4C 63 51 10 4D 85 D2 0F 8E 30 03 00 00 45 33 C0");
			if (BytePattern::temp_instance().has_size(1, "ファイル名を文字化けしないように設定")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jle     locret_xxxxx
				fileNameProc1ReturnAddress = Injector::GetBranchDestination(address + 7).as_int();

				Injector::MakeJMP(address, fileNameProc1, true);
			}
			else {
				e.unmatch.general = true;
			}
			break;
		default:
			e.version.general = true;
		}

		return e;
	}

	DllError fileNameProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// lea     rcx, [rbp-60h]
			BytePattern::temp_instance().find_pattern("48 8D 4D A0 E8 6C E9 6D 00 4C 8B 44 24 78");
			if (BytePattern::temp_instance().has_size(1, "UTF-8に変換して保存")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// lea     rcx, [rbp-60h]
				fileNameProc2CallAddress = Injector::GetBranchDestination(address + 4).as_int();

				// cmp     r8, 10h
				fileNameProc2ReturnAddress = address + 14;

				fileNameProcEscapedStrToUtf8 = (uintptr_t)escapedStrToUtf8;
				fileNameProcReplaceTextObject = (uintptr_t)replaceTextObject;

				Injector::MakeJMP(address, fileNameProc2, true);
			}
			else {
				e.unmatch.general = true;
			}
			break;
		default:
			e.version.general = true;
		}

		return e;
	}

	DllError fileNameProc3Injector(RunOptions options) {
		DllError e = {};
		
		switch (options.version) {
		case v3_3_0:
			// 
			BytePattern::temp_instance().find_pattern("48 8B 16 48 8B CA 41 B0 01 0F B6 02 84 C0");
			if (BytePattern::temp_instance().has_size(2, "UTF-8の完全なファイル名列挙")) {
				// jz short loc_XXXXX -> jmp XXXXX
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(14),0xEB,true);
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_second().address(14), 0xEB, true);
			}
			else {
				e.unmatch.general = true;
			}
			break;
		default:
			e.version.general = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= fileNameProc1Injector(options);
		result |= fileNameProc2Injector(options);
		result |= fileNameProc3Injector(options);

		return result;
	}
}