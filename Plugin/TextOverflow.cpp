#include "stdinc.h"
#include "byte_pattern.h"

namespace TextOerflow
{
	/*-----------------------------------------------*/

	uintptr_t cc_4_end_v28;
	__declspec(naked) void cc_1_start_v28()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz cc_10;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz cc_11;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz cc_12;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz cc_13;

			movzx eax, byte ptr[eax + esi];
			jmp cc_3;

		cc_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp cc_6;

		cc_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp cc_6;

		cc_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp cc_6;

		cc_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;

		cc_6:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja cc_2;
			mov eax, NOT_DEF;

		cc_2:
			add esi, 2;

		cc_3:
			mov ecx, [esp + 0x48 - 0x28];

			push cc_4_end_v28;
			ret;
		}
	}

	uintptr_t cc_4_end_v301;
	__declspec(naked) void cc_1_start_v301()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz cc_10;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz cc_11;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz cc_12;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz cc_13;

			movzx eax, byte ptr[eax + esi];
			jmp cc_3;

		cc_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp cc_6;

		cc_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp cc_6;

		cc_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp cc_6;

		cc_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;

		cc_6:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja cc_3;
			mov eax, NOT_DEF;

		cc_3:
			mov ecx, [esp + 0x48 - 0x2C]; // 修正された

			push cc_4_end_v301;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix1_hook(RunOptions *options) {
		std::string desc = "fix";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
			byte_pattern::temp_instance().find_pattern("0F B6 04 30 8B 4C 24");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// movzx eax,byte ptr [eax+esi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), cc_1_start_v28);
				// mov ecx,[ecx + eax*4+0xA4]
				cc_4_end_v28 = byte_pattern::temp_instance().get_first().address(8);
			}
			else return CK2ERROR1;
			return NOERROR;
		case v3_0_X:
			byte_pattern::temp_instance().find_pattern("0F B6 04 30 8B 4C 24");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// movzx eax,byte ptr [eax+esi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), cc_1_start_v301);
				// mov ecx,[ecx + eax*4+0xA4]
				cc_4_end_v301 = byte_pattern::temp_instance().get_first().address(8);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t text_over_flow_end_v301;
	__declspec(naked) void text_over_flow_start_v301()
	{
		__asm {
			mov     ecx, [edi + 0x14];
			cmp     ecx, 0x10;

			jb cc_01;
			mov     eax, [edi];
			jmp cc_02;

		cc_01:
			mov     eax, edi;

		cc_02:

			mov     ecx, [edi + 0x10];

			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz cc_10;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz cc_10;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz cc_10;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz cc_10;

			inc esi;
			jmp cc_2;

		cc_10:
			add esi, 3;

		cc_2:
			mov dword ptr [esp + 0x48 - 0x28], ecx;
			push text_over_flow_end_v301;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix2_hook(RunOptions *options) {
		std::string desc = "fix";

		switch (options->version) {
		case v3_0_X:
			byte_pattern::temp_instance().find_pattern("8B 4F 10 46 89 4C 24 20");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov     ecx, [edi+10h]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), text_over_flow_start_v301);
				// cmp     esi, ecx
				text_over_flow_end_v301 = byte_pattern::temp_instance().get_first().address(8);
			}
			else return CK2ERROR1;
			return NOERROR;
		default:
			return NOERROR;

		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = NOERROR;

		//テキストが溢れたときの ... の省略
		byte_pattern::debug_output2("Text overflow");

		//
		//result |= fix1_hook(options);

		// カウンタは後で進める
		//result |= fix2_hook(options);

		return result;
	}

}