#include "pch.h"
#include "plugin_64.h"
#include <atlstr.h>

namespace WordOrder {
	extern "C" {
		void wordOrderProc1();
		void wordOrderProc2();

		uintptr_t insert;
		uintptr_t append;
		uintptr_t constructFromKey;
		uintptr_t appendFromStatic;
		uintptr_t constructFromStatic;

	
		uintptr_t year;
		uintptr_t month;
		uintptr_t day;

		uintptr_t wordOrderProc1ReturnAddress;
		uintptr_t wordOrderProc2ReturnAddress;
	}

	ParadoxTextObject _year;
	ParadoxTextObject _month;
	ParadoxTextObject _day;

	DllError insertInjector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// mov     [rsp+arg_10], rbx
			BytePattern::temp_instance().find_pattern("48 89 5C 24 18 55 41 56 41 57 48 83 EC 20 4D 8B F0");
			if (BytePattern::temp_instance().has_size(1, u8"std::basic_string<char>#insertをフック")) {
				insert = BytePattern::temp_instance().get_first().address();
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

	DllError wordOrderProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// nop
			BytePattern::temp_instance().find_pattern("90 4C 8D 45 D0 48 8D 55 90 48 8D 4D B0");
			if (BytePattern::temp_instance().has_size(2, u8"日付の順番を入れ替え")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				append = Injector::GetBranchDestination(address + 0xD).as_int();

				// nop
				wordOrderProc1ReturnAddress = address + 0x48;

				Injector::MakeJMP(address, wordOrderProc1, true);

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

	DllError wordOrderProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// nop
			BytePattern::temp_instance().find_pattern("90 49 8B 07 48 8D 55 40 49 8B CF");
			if (BytePattern::temp_instance().has_size(1, u8"issue-32 「家 XXX」を「XXX家」にしたい")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				constructFromKey = Injector::GetBranchDestination(address + 0x1C).as_int();
				constructFromStatic = Injector::GetBranchDestination(address - 5).as_int();
				appendFromStatic = Injector::GetBranchDestination(address + 0x30).as_int();

				// mov rdx, rax
				wordOrderProc2ReturnAddress = address + 0x69;

				Injector::MakeJMP(address, wordOrderProc2, true);

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

		_day.t.text[0] = 0xE;
		_day.t.text[1] = '\0';
		_day.len = 1;
		_day.len2 = 0xF;

		_year.t.text[0] = 0xF;
		_year.t.text[1] = '\0';
		_year.len = 1;
		_year.len2 = 0xF;

		_month.t.text[0] = 7;
		_month.t.text[1] = '\0';
		_month.len = 1;
		_month.len2 = 0xF;

		year = (uintptr_t)&_year;
		month = (uintptr_t)&_month;
		day = (uintptr_t)&_day;

		result |= insertInjector(options);
		result |= wordOrderProc1Injector(options);
		result |= wordOrderProc2Injector(options);

		return result;
	}
}