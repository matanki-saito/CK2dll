#include "pch.h"
#include "plugin_64.h"

namespace FileName {
	extern "C" {
		void fileNameProc1();

		uintptr_t fileNameProc1ReturnAddress;
	}

	DllError fileNameProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movsxd  r10, dword ptr [rcx+10h]
			BytePattern::temp_instance().find_pattern("4C 63 51 10 4D 85 D2 0F 8E 30 03 00 00 45 33 C0");
			if (BytePattern::temp_instance().has_size(1, "ÉtÉ@ÉCÉãñºÇï∂éöâªÇØÇµÇ»Ç¢ÇÊÇ§Ç…ê›íË")) {
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

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= fileNameProc1Injector(options);

		return result;
	}
}