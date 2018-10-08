#include "stdinc.h"
#include "byte_pattern.h"

namespace MapView {
	/*-----------------------------------------------*/

	errno_t init(CK2Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("font view");

		result |= map1_2_hook(version);
		result |= map3_hook(version);
		result |= map4_hook(version);

		return result;
	}
}