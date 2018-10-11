#include "stdinc.h"
#include "byte_pattern.h"

namespace IME
{
	/*-----------------------------------------------*/

	errno_t SDL_windowskeyboard_Win_StartTextInput_hook(CK2Version version) {
		std::string desc = "SDL_windowskeyboard Win_StartTextInput";

		switch (version) {
		case v2_8_X:
			// skip
			//IME_Init(videodata, hwnd);
			//IME_Enable(videodata, hwnd);
			byte_pattern::temp_instance().find_pattern("8B 8A 90 00 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc + " skip code")) {
				injector::MakeJMP(
					byte_pattern::temp_instance().get_first().address(0x28),// push edi
					byte_pattern::temp_instance().get_first().address(0x36) // add esp 1Ch
				);
				// ŠÖ”‚ğ‚Q‚ÂÁ‚·‚Ì‚ÅAadd esp 1Ch -> 0C
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x36 + 2), 0x0C, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t SDL_windowskeyboard_Win_StopTextInput_hook(CK2Version version) {
		std::string desc = "SDL_windowskeyboard Win_StopTextInput";

		switch (version) {
		case v2_8_X:
			// skip
			//IME_Init(videodata, hwnd);
			//IME_Enable(videodata, hwnd);
			byte_pattern::temp_instance().find_pattern("8B 80 90 00 00 00 56 57");
			if (byte_pattern::temp_instance().has_size(1, desc + " skip code")) {
				injector::MakeJMP(
					byte_pattern::temp_instance().get_first().address(0xE),// push edi
					byte_pattern::temp_instance().get_first().address(0x25) //pop edi
				);
				// ŠÖ”‚ğ‚Q‚ÂÁ‚·‚Ì‚ÅAadd esp 10h -> 0
				//injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x14 + 2), 0x8, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t SDL_windowskeyboard_Win_IME_HandleMessage_hook(CK2Version version) {
		std::string desc = "SDL_windowskeyboard Win_IME_HandleMessage";

		switch (version) {
		/* show candidate and composition window */
		// see https://twitter.com/matanki_saito/status/1005093384946479104
		case v2_8_X:
			// skip
			// if (!videodata->ime_initialized || !videodata->ime_available || !videodata->ime_enabled)
			//    return SDL_FALSE;
			byte_pattern::temp_instance().find_pattern("39 4E 28 0F 84 19 02");
			if (byte_pattern::temp_instance().has_size(1, desc + " skip code")) {
				injector::MakeJMP(
					byte_pattern::temp_instance().get_first().address(0),
					byte_pattern::temp_instance().get_first().address(0x1B)
				);
			}
			else return CK2ERROR1;

			// skip (remove)
			// *lParam = 0;
			byte_pattern::temp_instance().find_pattern("8B 45 14 89 08 E9 83 00");
			if (byte_pattern::temp_instance().has_size(1, desc + " skip code")) {
				injector::MakeNOP(
					byte_pattern::temp_instance().get_first().address(),
					5,
					true
				);
			}
			else return CK2ERROR1;

			// skip
			//if (*lParam & GCS_RESULTSTR) {
			//    IME_GetCompositionString(videodata, himc, GCS_RESULTSTR);
			//    IME_SendInputEvent(videodata);
			//}
			//if (*lParam & GCS_COMPSTR) {
			//    if (!videodata->ime_uiless)
			//        videodata->ime_readingstring[0] = 0;

			//    IME_GetCompositionString(videodata, himc, GCS_COMPSTR);
			//    IME_SendEditingEvent(videodata);
			//}
			byte_pattern::temp_instance().find_pattern("B9 00 08 00 00 8B 45");
			if (byte_pattern::temp_instance().has_size(1, desc + " skip code")) {
				injector::MakeJMP(
					byte_pattern::temp_instance().get_first().address(0x8),
					byte_pattern::temp_instance().get_first().address(-0x25)
				);
			}
			else return CK2ERROR1;

			// skip (remove)
			// SDL_SendEditingText("",0,0)
			//byte_pattern::temp_instance().find_pattern("51 33 C0 51 66 89 46 40");
			//if (byte_pattern::temp_instance().has_size(1, desc + " skip code")) {

			//	injector::MakeNOP(
			//		byte_pattern::temp_instance().get_first().address(0x1D),
			//		5,
			//		true
			//	);
			//}
			//else return CK2ERROR1;
			return NOERROR;

		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	// insert 
	//videodata->ime_hwnd_current = hwnd;
	//rect.x = 0;
	//rect.y = 0;
	//SDL_SetTextInputRect(&rect);
	uintptr_t settingInputRect_v28_end;
	uintptr_t settingInputRect_v28_end2;
	uintptr_t SDL_SetTextInputRect_v28;
	__declspec(naked) void settingInputRect_v28_start() {
		__asm {
			jz zz_5;

			push settingInputRect_v28_end;
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
			call SDL_SetTextInputRect_v28;
			add esp, 0x0C;

			push settingInputRect_v28_end2;
			ret;
		}
	}

	/*-----------------------------------------------*/
	
	errno_t SDL_windowskeyboard_Win_IME_HandleMessage_WM_IME_STARTCOMPOSITION_hook(CK2Version version) {
		std::string desc = "SDL_windowskeyboard Win_IME_HandleMessage WM_IME_STARTCOMPOSITION";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("0F 84 FD 00 00 00 83 E8 01");
			if (byte_pattern::temp_instance().has_size(1, desc + " insert code start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), settingInputRect_v28_start);
				settingInputRect_v28_end = byte_pattern::temp_instance().get_first().address(0x06);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("33 DB 43 E9 E5");
			if (byte_pattern::temp_instance().has_size(1, desc + " insert code end2")) {
				settingInputRect_v28_end2 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("55 8B EC A1 ? ? ? ? 85 C0 74 12 8B");
			if (byte_pattern::temp_instance().has_size(1, desc + " get SDL_SetTextInputRect addr")) {
				SDL_SetTextInputRect_v28 = byte_pattern::temp_instance().get_first().address();
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

	// skip
	//if (IME_HandleMessage(hwnd, msg, wParam, &lParam, data->videodata)) {
	//	goto A;
	//}
	uintptr_t SDL_windowevent_v28_end;
	uintptr_t SDL_windowevent_v28_end2;
	__declspec(naked) void SDL_windowevent_v28_start() {
		__asm {
			add esp, 0x14;
			test eax, eax;
			jz end2_jmp;

			push SDL_windowevent_v28_end;
			ret;

		end2_jmp:
			push SDL_windowevent_v28_end2;
			ret;
		}
	}

	/*-----------------------------------------------*/
	
	errno_t SDL_windowevent_hook(CK2Version version) {
		std::string desc = "SDL_windowevent";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("83 C4 14 85 C0 74 07 33");
			if (byte_pattern::temp_instance().has_size(1, desc + " start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), SDL_windowevent_v28_start);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("FF 75 14 FF 75 10 FF 75 0C FF 75 08 E9 B0 0D 00");
			if (byte_pattern::temp_instance().has_size(1, desc + " end1")) {
				SDL_windowevent_v28_end = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("8B 45 0C B9 01 01 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc + " end2")) {
				SDL_windowevent_v28_end2 = byte_pattern::temp_instance().get_first().address();
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

		// SDL_windowskeyboard.c Win_StartTextInput‚ğC³
		result |= SDL_windowskeyboard_Win_StartTextInput_hook(version);
		// SDL_windowskeyboard.c Win_StopTextInput‚ğC³
		result |= SDL_windowskeyboard_Win_StopTextInput_hook(version);
		// SDL_windowskeyboard Win_IME_HandleMessage‚ğC³
		result |= SDL_windowskeyboard_Win_IME_HandleMessage_hook(version);
		// SDL_windowsevent.c‚ÉInputRect‚ğİ’è‚·‚éƒR[ƒh‚ğ’Ç‰Á‚·‚é
		result |= SDL_windowskeyboard_Win_IME_HandleMessage_WM_IME_STARTCOMPOSITION_hook(version);

		// SDL_keyborad.c‚ğC³
		result |= SDL_keyborad_hook(version);
		// SDL_windowevent.c‚ğ•ÏX
		result |= SDL_windowevent_hook(version);

		return result;
	}
}