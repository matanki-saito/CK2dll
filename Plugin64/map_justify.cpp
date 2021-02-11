#include "pch.h"
#include "plugin_64.h"

namespace MapJustify {
	extern "C" {
		void mapJustifyProc1();
		void mapJustifyProc2();
		void mapJustifyProc3();
		void mapJustifyProc4();
		void mapJustifyProc4v3332();
		uintptr_t mapJustifyProc1ReturnAddress1;
		uintptr_t mapJustifyProc1ReturnAddress2;
		uintptr_t mapJustifyProc2ReturnAddress;
		uintptr_t mapJustifyProc3ReturnAddress;
		uintptr_t mapJustifyProc4ReturnAddress;
	}

	DllError mapJustifyProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movsd   xmm3, [rbp+1B0h+var_190]
			BytePattern::temp_instance().find_pattern("F2 0F 10 5D 20 FF C6 F2 0F 10 65 28");
			if (BytePattern::temp_instance().has_size(1, u8"文字取得処理リターン先２")) {
				mapJustifyProc1ReturnAddress2 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.unmatch.mapJustifyProc1Injector = true;
			}

			// movzx   eax, byte ptr [r14+rax]
			BytePattern::temp_instance().find_pattern("41 0F B6 04 06 4C 8B 14 C1 4D 85 D2");
			if (BytePattern::temp_instance().has_size(1, u8"文字取得処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cmp     dword ptr [r10+0Ch], 0
				mapJustifyProc1ReturnAddress1 = address + 0x12;

				Injector::MakeJMP(address, mapJustifyProc1, true);
			}
			else {
				e.unmatch.mapJustifyProc1Injector = true;
			}
			break;
		default:
			e.version.mapJustifyProc1Injector = true;
		}

		return e;
	}

	DllError mapJustifyProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// lea     eax, [rdx-1]
			BytePattern::temp_instance().find_pattern("8D 42 FF 45 0F 57 C0 F3 44 0F 10 C0");
			if (BytePattern::temp_instance().has_size(1, u8"一文字表示の調整")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cvtdq2ps xmm6, xmm6
				mapJustifyProc2ReturnAddress = address + 0x19;

				Injector::MakeJMP(address, mapJustifyProc2, true);
			}
			else {
				e.unmatch.mapJustifyProc2Injector = true;
			}
			break;
		default:
			e.version.mapJustifyProc2Injector = true;
		}

		return e;
	}

	DllError mapJustifyProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movsd   xmm3, [rbp+1D0h+var_168]
			BytePattern::temp_instance().find_pattern("F2 0F 10 5D 20 FF C6 F2 0F 10 65 28");
			if (BytePattern::temp_instance().has_size(1, u8"カウント処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cmp     r13, rax
				mapJustifyProc3ReturnAddress = address + 0x24;

				Injector::MakeJMP(address, mapJustifyProc3, true);
			}
			else {
				e.unmatch.mapJustifyProc3Injector = true;
			}
			break;
		default:
			e.version.mapJustifyProc3Injector = true;
		}

		return e;
	}

	// これはwin32のときはMapAdj2としてあったもの。Proc1～3とは別のprocにinjectしている
	DllError mapJustifyProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movzx   eax, byte ptr [rdi+rax]
			BytePattern::temp_instance().find_pattern("0F B6 04 07 4D 8B 94 C4 E8 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"文字取得処理 v.3.3.3.[0-1]")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz      loc_xxxxx
				mapJustifyProc4ReturnAddress = address + 0x0F;

				Injector::MakeJMP(address, mapJustifyProc4, true);
			}
			else {
				// versionが全く同じなまま更新されてしまった（3.3.3 -> 3.3.3）
				// movzx   eax, byte ptr [rsi+rax]
				BytePattern::temp_instance().find_pattern("0F B6 04 06 4D 8B 94 C4 E8 00 00 00");
				if (BytePattern::temp_instance().has_size(1, u8"文字取得処理 v3.3.3.2")) {
					uintptr_t address = BytePattern::temp_instance().get_first().address();

					// jz      loc_xxxxx
					mapJustifyProc4ReturnAddress = address + 0x0F;

					Injector::MakeJMP(address, mapJustifyProc4v3332, true);
				}
				else {
					e.unmatch.mapJustifyProc4Injector = true;
				}
			}
			break;
		default:
			e.version.mapJustifyProc4Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mapJustifyProc1Injector(options);
		result |= mapJustifyProc2Injector(options);
		result |= mapJustifyProc3Injector(options);
		result |= mapJustifyProc4Injector(options);

		return result;
	}
}