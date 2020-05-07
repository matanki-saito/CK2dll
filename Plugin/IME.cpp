#include "stdinc.h"
#include "byte_pattern.h"

namespace IME
{
	/*-----------------------------------------------*/
	
	errno_t SDL_windowskeyboard_Win_StartTextInput_hook(RunOptions *options) {
		std::string desc = "SDL_windowskeyboard Win_StartTextInput";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
			// skip
			//IME_Init(videodata, hwnd);
			//IME_Enable(videodata, hwnd);
			byte_pattern::temp_instance().find_pattern("8B 4D 08 8B B1 9C 02 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc + " skip code")) {
				injector::MakeJMP(
					byte_pattern::temp_instance().get_first().address(0x1D),// push edi
					byte_pattern::temp_instance().get_first().address(0x2B) // add esp 1Ch
				);
				// 関数を２つ消すので、add esp 1Ch -> 0C
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x2B + 2), 0x0C, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t SDL_windowskeyboard_Win_StopTextInput_hook(RunOptions *options) {
		std::string desc = "SDL_windowskeyboard Win_StopTextInput";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
			// skip
			//IME_Init(videodata, hwnd);
			//IME_Enable(videodata, hwnd);
			byte_pattern::temp_instance().find_pattern("8B 80 90 00 00 00 56 57");
			if (byte_pattern::temp_instance().has_size(1, desc + " skip code")) {
				injector::MakeJMP(
					byte_pattern::temp_instance().get_first().address(0xE),// push edi
					byte_pattern::temp_instance().get_first().address(0x25) //pop edi
				);
				// 関数を２つ消すので、add esp 10h -> 0
				//injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x14 + 2), 0x8, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t SDL_windowskeyboard_Win_IME_HandleMessage_hook(RunOptions *options) {
		std::string desc = "SDL_windowskeyboard Win_IME_HandleMessage";

		switch (options->version) {
		/* show candidate and composition window */
		// see https://twitter.com/matanki_saito/status/1005093384946479104
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
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
	
	errno_t SDL_windowskeyboard_Win_IME_HandleMessage_WM_IME_STARTCOMPOSITION_hook(RunOptions *options) {
		std::string desc = "SDL_windowskeyboard Win_IME_HandleMessage WM_IME_STARTCOMPOSITION";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
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

	errno_t SDL_keyborad_hook(RunOptions *options) {
		std::string desc = "SDL_keyborad";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
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
	
	errno_t SDL_windowevent_hook(RunOptions *options) {
		std::string desc = "SDL_windowevent";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
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
	} //

	/*-----------------------------------------------*/

	uintptr_t SDL_SendKeyboardKey_v28;
	uintptr_t issue31_v28_end;
	__declspec(naked) void issue31_v28_start() {
		__asm {
			cmp esi, 229;
			jz issue31_x; // skip

			call SDL_SendKeyboardKey_v28;

		issue31_x:
			pop ecx;
			push issue31_v28_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t SDL_windowevent_issue31_hook(RunOptions *options) {
		std::string desc = "SDL_windowevent issue31";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
			// 少し手前に引っ掛ける
			byte_pattern::temp_instance().find_pattern("8B 45 10 59 59 50 6A 00");
			if (byte_pattern::temp_instance().has_size(1, desc + " start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(8), issue31_v28_start);
				issue31_v28_end = byte_pattern::temp_instance().get_first().address(0xE);
			}
			else return CK2ERROR1;

			// SDL_SendKeyboardKeyを見つける
			byte_pattern::temp_instance().find_pattern("55 8B EC 83 EC 40 56 8B 75 0C 85 F6");
			if (byte_pattern::temp_instance().has_size(1, desc + " SDL_SendKeyboardKey")) {
				SDL_SendKeyboardKey_v28 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			return NOERROR;
		}
		return CK2ERROR1;
	} //

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("IME fix");

		// SDL_windowskeyboard.c Win_StartTextInputを修正
		result |= SDL_windowskeyboard_Win_StartTextInput_hook(options);
		// SDL_windowskeyboard.c Win_StopTextInputを修正
		result |= SDL_windowskeyboard_Win_StopTextInput_hook(options);
		// SDL_windowskeyboard Win_IME_HandleMessageを修正
		result |= SDL_windowskeyboard_Win_IME_HandleMessage_hook(options);
		// SDL_windowskeyboard.cにInputRectを設定するコードを追加する
		result |= SDL_windowskeyboard_Win_IME_HandleMessage_WM_IME_STARTCOMPOSITION_hook(options);

		// SDL_keyborad.cを修正
		result |= SDL_keyborad_hook(options);
		// SDL_windowevent.cを変更
		result |= SDL_windowevent_hook(options);
		// SDL_windowsevent.cを変更
		result |= SDL_windowevent_issue31_hook(options);

		return result;
	}
}