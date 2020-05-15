#include "pch.h"
#include "plugin_64.h"
#include "escape_tool.h"

namespace FileName {
	extern "C" {
		void fileNameProc1();
		void fileNameProc2();
		void fileNameProc4();
		void fileNameProc5();

		uintptr_t fileNameProc1ReturnAddress;
		uintptr_t fileNameProc2CallAddress;
		uintptr_t fileNameProcEscapedStrToUtf8;
		uintptr_t fileNameProcUtf8ToEscapedStr;
		uintptr_t fileNameProcReplaceTextObject;
		uintptr_t fileNameProc2ReturnAddress;
		uintptr_t fileNameProc4ReturnAddress;
		uintptr_t fileNameProc5ReturnAddress;
		uintptr_t fileNameProc5CallAddress;
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
			// mov     [rsp+210h+var_1D8], 0Fh
			BytePattern::temp_instance().find_pattern("48 C7 44 24 38 0F 00 00 00 48 89 7C 24 30 C6 44 24 20 00 48 8D 54 24 60");
			if (BytePattern::temp_instance().has_size(1, "UTF-8に変換して保存")) {
				// lea     rcx, [rbp+110h+var_170]
				uintptr_t address = BytePattern::temp_instance().get_first().address() + 0x18;

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

	DllError fileNameProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// mov r9d, esi
			BytePattern::temp_instance().find_pattern("44 8B CE 45 33 C0 48 8D 54 24 60 49 8D 4F 50");
			if (BytePattern::temp_instance().has_size(1, "UTF-8のファイル名の変換")) {
				fileNameProcUtf8ToEscapedStr = (uintptr_t)utf8ToEscapedStr2;

				// nop
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				Injector::MakeJMP(address + 0x14, fileNameProc4, true);


				// mov     byte ptr [rsp+130h+Dst], 0
				fileNameProc4ReturnAddress = address + 0x23;

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


	DllError fileNameProc5Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// 場所は適当
			// call    sub_xxxxx
			BytePattern::temp_instance().find_pattern("E8 FA DE 27 00 90 4C 8B 44 24 58 49 83 F8 10 72 12");
			if (BytePattern::temp_instance().has_size(1, "UTF-8のファイル名の変換")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call    sub_{xxxxx}
				fileNameProc5CallAddress = Injector::GetBranchDestination(address).as_int();

				// call    sub_{xxxxx}
				Injector::MakeJMP(address, fileNameProc5, true);

				// jb      short loc_xxxxx
				fileNameProc5ReturnAddress = address + 15;

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
		result |= fileNameProc4Injector(options);
		// 効果不明のため、コメントアウト
		//result |= fileNameProc5Injector(options);

		return result;
	}
}