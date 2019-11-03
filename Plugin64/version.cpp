#include "pch.h"
#include "plugin_64.h"

using namespace std;

namespace Version {
	typedef struct {
		char ascii1;
		char ascii2;
		char dot;
		char ascii3;

		int calVer() {
			int ver = (ascii1 - 0x30) * 100 + (ascii2 - 0x30) * 10 + (ascii3 - 0x30);
			return ver;
		}
	} Pattern;

	string versionString(Ck2Version version) {
		switch (version) {
		case v3_3_0:
			return "v3_3_0";
		default:
			return "UNKNOWN";
		}
	}

	Ck2Version GetVersion() {
		// CK2 v3.??.?
		BytePattern::temp_instance().find_pattern("45 55 34 20 76 31 2E ? ? 2E ?");
		if (BytePattern::temp_instance().count() > 0) {
			// ??を取得する
			Pattern minor = Injector::ReadMemory<Pattern>(BytePattern::temp_instance().get_first().address(0x7), true);

			Ck2Version version;

			switch (minor.calVer()) {
			case 330:
				version = v3_3_0;
				break;
			default:
				version = UNKNOWN;
				break;
				;;
			}

			BytePattern::LoggingInfo(versionString(version));

			return version;
		}
		else return UNKNOWN;
	}
}