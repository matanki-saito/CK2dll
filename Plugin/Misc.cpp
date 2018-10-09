#include "stdinc.h"
#include "byte_pattern.h"

namespace Misc {
	/*-----------------------------------------------*/

	errno_t dateOrder_hook(CK2Version version) {
		std::string desc = "date order fix";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("64 20 77 20 6D 77 20 2C");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0), 0x79, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(1), 0x20, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x10, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x74, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(4), 0x5E, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(5), 0x20, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(6), 0x6D, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(7), 0x77, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(8), 0x20, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(9), 0x64, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(10), 0x20, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(11), 0x10, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(12), 0xE5, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(13), 0x65, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(CK2Version version) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("misc");

		result |= dateOrder_hook(version);

		return result;
	}
}