#include "pch.h"
#include "plugin_64.h"

namespace Localize {
	extern "C" {
		void localizeProc1();

		uintptr_t localizeProc1ReturnAddress1;
		uintptr_t localizeProc1ReturnAddress2;
	}

	DllError localizeProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// lea     rcx, [rsp+128h+var_F8]
			BytePattern::temp_instance().find_pattern("48 8D 4C 24 30 49 83 F9 10 49 0F 43 C8 41 8D 42 FF");
			if (BytePattern::temp_instance().has_size(2, "dynastyに-idがついてしまう問題のreturn address")) {
				uintptr_t address = BytePattern::temp_instance().get_second().address();

				// jump先が複数見つかるので、この方法を使う
				// jz {xxxxx}
				localizeProc1ReturnAddress1 = Injector::GetBranchDestination(address + 0x17).as_int();
			}
			else {
				e.unmatch.general = true;
			}
			break;
		default:
			e.version.general = true;
		}
		
		switch (options.version) {
		case v3_3_0:
			// mov     r8, [rsp+128h+var_F8]
			BytePattern::temp_instance().find_pattern("4C 8B 44 24 30 4C 8B 4C 24 48 41 83 FA 04");
			if (BytePattern::temp_instance().has_size(1, "dynastyに-idがついてしまう問題")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				Injector::MakeJMP(address, localizeProc1, true);

				// jle     loc_xxxxx
				localizeProc1ReturnAddress2 = address + 14;
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

		result |= localizeProc1Injector(options);

		return result;
	}
}