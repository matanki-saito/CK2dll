#include "pch.h"
#include "plugin_64.h"

namespace Unk {
	extern "C" {
		void unkProc1();
		uintptr_t unkProc1ReturnAddress;
	}

	DllError unkProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movzx   eax, byte ptr [rax+rdi]
			BytePattern::temp_instance().find_pattern("0F B6 04 38 4D 8B 94 C5 E8 00 00 00");
			if (BytePattern::temp_instance().has_size(1, "ï∂éöéÊìæèàóù")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz      loc_xxxxx
				unkProc1ReturnAddress = address + 0x0F;

				Injector::MakeJMP(address, unkProc1, true);
			}
			else {
				e.unmatch.unkProc1Injector = true;
			}
			break;
		default:
			e.version.unkProc1Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= unkProc1Injector(options);

		return result;
	}
}