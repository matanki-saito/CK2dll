#include "stdinc.h"
#include "byte_pattern.h"

namespace IME
{
	/*-----------------------------------------------*/

	uintptr_t zz_4;
	uintptr_t loc_18C8D09;
	__declspec(naked) void SDL_SetTextInputRect_f1() {
		__asm {
			nop;
			nop;
			nop;
			add eax, 5;
		}
	}

	__declspec(naked) void zz_2() {
		__asm {
			jz zz_5;
			
			push zz_4;
			ret;

		zz_5:
			sub esp, 8;
			mov ecx, [ebp + 0x18];
			mov edx, [ebp + 8];
			mov[ecx + 0x38], edx;
			mov dword ptr[ebp - 0x14], 0;
			mov dword ptr[ebp - 0x10], 0;
			lea eax, [ebp - 0x14];
			push eax;
			call SDL_SetTextInputRect_f1;
			add esp, 0x0C;
			
			push loc_18C8D09;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t SDL_windowskeyboard_hook(CK2Version version) {
		std::string desc = "SDL_windowskeyboard";

		switch (version) {
		case v2_8_X:
			/* show candidate and composition window */
			// see https://twitter.com/matanki_saito/status/1005093384946479104
			//
			// (SDL_windowskeyboard.c)
			//
			// skip
			//if (*lParam & GCS_RESULTSTR) {
			//    IME_GetCompositionString(videodata, himc, GCS_RESULTSTR);
			//    IME_SendInputEvent(videodata);
			//}
			byte_pattern::temp_instance().find_pattern("B9 00 08 00 00 8B 45");
			if (byte_pattern::temp_instance().has_size(1, desc + " skip code")) {
				injector::MakeJMP(
					byte_pattern::temp_instance().get_first().address(0x8),
					byte_pattern::temp_instance().get_first().address(0x37)
				);
			}
			else return CK2ERROR1;

			// remove
			// *lParam = 0;
			byte_pattern::temp_instance().find_pattern("8B 45 14 89 08 E9 83 00");
			if (byte_pattern::temp_instance().has_size(1, "remove code")) {
				injector::MakeNOP(
					byte_pattern::temp_instance().get_first().address(),
					5,
					true
				);
			}
			else return CK2ERROR1;

			// skip
			//if (!videodata->ime_initialized || !videodata->ime_available || !videodata->ime_enabled)
			//    return SDL_FALSE;
			byte_pattern::temp_instance().find_pattern("39 4E 28 0F 84 19 02");
			if (byte_pattern::temp_instance().has_size(1,desc + "skip code")) {
				injector::MakeJMP(
					byte_pattern::temp_instance().get_first().address(0),
					byte_pattern::temp_instance().get_first().address(0x1B)
				);
			}
			else return CK2ERROR1;

			// insert 
			//videodata->ime_hwnd_current = hwnd;
			//rect.x = 0;
			//rect.y = 0;
			//SDL_SetTextInputRect(&rect);
			byte_pattern::temp_instance().find_pattern("0F 84 FD 00 00 00 83 E8 01");
			if (byte_pattern::temp_instance().has_size(1, desc + " insert code")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), zz_2);
				zz_4 = byte_pattern::temp_instance().get_first().address(0x06);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("33 DB 43 E9 E5");
			if (byte_pattern::temp_instance().has_size(1, desc + " insert code end1")) {
				loc_18C8D09 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("55 8B EC A1 ? ? ? ? 85 C0 74 12 8B");
			if (byte_pattern::temp_instance().has_size(1, desc + " SDL_SetTextInputRect")) {
				injector::MakeJMP(SDL_SetTextInputRect_f1, byte_pattern::temp_instance().get_first().address());
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/
	
	errno_t SDL_keyborad_hook(CK2Version version) {
		std::string desc = "SDL_keyborad";

		switch (version) {
		case v2_8_X:
			// SDL_keyborad.c
			// skip
			// issue-9
			//byte_pattern::temp_instance().find_pattern("85 F6 74 30 57 57 6A 0C");
			//if (byte_pattern::temp_instance().has_size(1)) {
			//	injector::MakeJMP(
			//		byte_pattern::temp_instance().get_first().address(-0x6),
			//		byte_pattern::temp_instance().get_first().address(0)
			//	);
			//}
			//else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t zz_21;
	uintptr_t loc_18AB507;
	__declspec(naked) void zz_8() {
		__asm {
			add esp, 0x14;
			test eax, eax;
			jz loc_18AB507_jmp;

			push zz_21;
			ret;

		loc_18AB507_jmp:
			push loc_18AB507;
			ret;
		}
	}

	/*-----------------------------------------------*/
	
	errno_t SDL_windowevent_hook(CK2Version version) {
		std::string desc = "SDL_windowevent";

		switch (version) {
		case v2_8_X:
			// SDL_windowevent.c
			// insert goto
			//if (IME_HandleMessage(hwnd, msg, wParam, &lParam, data->videodata)) {
			//	goto A;
			//}
			byte_pattern::temp_instance().find_pattern("83 C4 14 85 C0 74 07 33");
			if (byte_pattern::temp_instance().has_size(1, desc + " start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), zz_8);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("FF 75 14 FF 75 10 FF 75 0C FF 75 08 E9 B0 0D 00");
			if (byte_pattern::temp_instance().has_size(1, desc + " end1")) {
				zz_21 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("8B 45 0C B9 01 01 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc + " end2")) {
				loc_18AB507 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(CK2Version version) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("IME fix");

		// SDL_windowskeyboard.c‚ğC³
		result |= SDL_windowskeyboard_hook(version);
		// SDL_keyborad.c‚ğC³
		result |= SDL_keyborad_hook(version);
		// SDL_windowevent.c‚ğ•ÏX
		result |= SDL_windowevent_hook(version);

		return result;
	}
}