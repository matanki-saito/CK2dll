#include "stdinc.h"
#include "byte_pattern.h"

namespace Misc {

	CK2Version getVersion() {

		CK2Version version = UNKNOWN;

		// _ _ 2.7.
		byte_pattern::temp_instance().find_pattern("00 00 32 2E 37 2E");
		if (byte_pattern::temp_instance().has_size(1,"v2.7.X pattern Check")) {
			version = v2_7_X;
			goto A;
		}

		// _ _ 2.8.
		byte_pattern::temp_instance().find_pattern("00 00 32 2E 38 2E");
		if (byte_pattern::temp_instance().has_size(1,"v2.8.X pattern Check")) {
			version = v2_8_X;
			goto A;
		}

		// _ _ 3.0
		byte_pattern::temp_instance().find_pattern("00 00 33 2E 30");
		if (byte_pattern::temp_instance().has_size(2, "v3.0.X pattern Check")) {
			version = v3_0_X;
			goto A;
		}

	A:
		byte_pattern::debug_output2(Misc::versionString(version));
		return version;
	}

	std::string versionString(CK2Version version) {
		switch (version) {
		case v2_7_X:
			return "v2_7_X";
		case v2_8_X:
			return "v2_8_X";
		case v3_0_X:
			return "v3_0_X";
		default:
			return "UNKNOWN";
		}
	}
}