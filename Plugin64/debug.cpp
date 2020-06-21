#include "pch.h"
#include "plugin_64.h"

namespace Debug {

	extern "C" {
		void debugProc1();
		uintptr_t debugProc1ReturnAddress;
	}

	DllError debugProc1Injector(RunOptions options) {
		DllError e = {};
		std::string pattern;

		switch (options.version) {
		case v3_3_0:
			pattern = "40 57 41 54 41 55 41 56 41 57 B8 F0 17 00 00";
			// hook main thread head
			// push rdi; push r12; ...
			BytePattern::temp_instance().find_pattern(pattern);
			if (BytePattern::temp_instance().has_size(1, u8"デバッグ")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call xxxxx
				debugProc1ReturnAddress = address + 15;

				Injector::MakeJMP(address, debugProc1, true);
			}
			else {
				e.unmatch.debugProc1Injector = true;
			}
			break;
		default:
			e.version.debugProc1Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};
		result |= debugProc1Injector(options);
		return result;
	}
}