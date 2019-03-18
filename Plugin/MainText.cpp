#include "stdinc.h"
#include "byte_pattern.h"

namespace MainText
{
	/*-----------------------------------------------*/

	errno_t stackSizeChange_hook(RunOptions *options) {
		std::string desc = "stack size change";
		
		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			// sub esp,428h
			byte_pattern::temp_instance().find_pattern("81 EC 28 04 00 00 56 57 8B F9");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x30, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/
	
	uintptr_t diff;

	/*-----------------------------------------------*/

	errno_t prepareBuffCopy_hook(RunOptions *options) {
		std::string desc = "prepare buff copy";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			// mov al, byte_XXXXXX[esi]
			byte_pattern::temp_instance().find_pattern("8A 86 ? ? ? ? 88 81 ? ? ? ? 41");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				char *pSRC = *byte_pattern::temp_instance().get_first().pointer<char *>(2);
				char *pDST = *byte_pattern::temp_instance().get_first().pointer<char *>(8);
	
				diff = pDST - pSRC;
	
				injector::WriteMemory<char *>(byte_pattern::temp_instance().get_first().address(8), pSRC, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0), 0x8D, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(1), 0x15, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(6), 0x8D, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(7), 0x15, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	int fontOffset = 0;

	uintptr_t b_3_end_v28;
	__declspec(naked) void b_2_v28()
	{
		__asm {
			mov[ebp - 0x43C], eax;

			lea eax, [edi + eax * 4];
			add eax,fontOffset; //edi + eax * 4 + OFFSET
			mov eax, [eax];
			mov[ebp - 0x3C], esi;

			push b_3_end_v28;
			ret;
		}
	}

	__declspec(naked) void b_6_start_v28()
	{
		__asm {
			movzx eax, al;
			jmp b_2_v28;
		}
	}

	uintptr_t b_5_end_v28;
	__declspec(naked) void b_1_start_v28()
	{
		__asm {
			push ebx;
			mov ebx, edx;
			add ebx, diff;
	
			mov al, [edx + esi];
			mov [ebx + ecx], al;
			inc ecx;
	
			cmp al, ESCAPE_SEQ_1;
			jz b_10;
	
			cmp al, ESCAPE_SEQ_2;
			jz b_11;
	
			cmp al, ESCAPE_SEQ_3;
			jz b_12;
	
			cmp al, ESCAPE_SEQ_4;
			jz b_13;
	
			jmp b_4;
	
		b_10:
			movzx eax, word ptr[edx + esi + 1];
			mov[ebx + ecx], ax;
			jmp b_1x;
	
		b_11:
			movzx eax, word ptr[edx + esi + 1];
			mov[ebx + ecx], ax;
			sub eax, SHIFT_2;
			jmp b_1x;
	
		b_12:
			movzx eax, word ptr[edx + esi + 1];
			mov[ebx + ecx], ax;
			add eax, SHIFT_3;
			jmp b_1x;
	
		b_13:
			movzx eax, word ptr[edx + esi + 1];
			mov[ebx + ecx], ax;
			add eax, SHIFT_4;
			jmp b_1x;
	
		b_1x:
			pop ebx;
	
			add esi, 2;
			add ecx, 2;
			mov edx, [ebp - 0x18];
			movzx eax, ax;
	
			cmp eax, NO_FONT;
			ja b_2_v28;
			mov eax, NOT_DEF;
			jmp b_2_v28;
	
		b_4:
			pop ebx;
	
			mov [ebp - 0x34], ecx;
			mov edx, [ebp - 0x18];
			test ah, ah;
			jz b_6_start_v28;
				
			push b_5_end_v28;
			ret;
		}
	};

	/*-----------------------------------------------*/

	errno_t func1_hook(RunOptions *options) {
		std::string desc = "func1";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			// inc ecx
			byte_pattern::temp_instance().find_pattern("41 89 4D CC 84 E4 0F");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), b_1_start_v28);
				b_5_end_v28 = byte_pattern::temp_instance().get_first().address(12);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t func2_hook(RunOptions *options) {
		std::string desc = "func2";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			// mov eax,[edi+eax*4+OFFSET]
			byte_pattern::temp_instance().find_pattern("8B 84 87 ? 00 00 00 89");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), b_6_start_v28);
				b_3_end_v28 = byte_pattern::temp_instance().get_first().address(7);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t c_2_end_v28;
	uintptr_t c_2_end2_v28;

	__declspec(naked) void c_1_start_v28()
	{
		__asm {
			cmp dword ptr [ebp - 0x2C], 0;
			jz c_2_jmp;
			cmp dword ptr[ebp - 0x43C], 0x100;
			jg c_2_jmp;

			push c_2_end2_v28;
			ret;

		c_2_jmp:
			push c_2_end_v28;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func3_hook(RunOptions *options) {
		std::string desc = "func3";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			// cmp dword ptr [ebp-2Ch],0
			byte_pattern::temp_instance().find_pattern("83 7D D4 00 0F 85 ? ? ? ? 8B 43");
			if (byte_pattern::temp_instance().has_size(1, desc + "start")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), c_1_start_v28);
				c_2_end_v28 = byte_pattern::temp_instance().get_first().address(10);
			}
			else return CK2ERROR1;

			// cmp byte_XXXXX, 0
			byte_pattern::temp_instance().find_pattern("80 3D ? ? ? ? 00 0F 84 47");
			if (byte_pattern::temp_instance().has_size(1, desc + " end2")) {
				c_2_end2_v28 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;

			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t view_end_v28;
	__declspec(naked) void view_start_v28()
	{
		__asm {
			mov al, [ecx + edx];

			cmp al, ESCAPE_SEQ_1;
			jz d_10;

			cmp al, ESCAPE_SEQ_2;
			jz d_11;

			cmp al, ESCAPE_SEQ_3;
			jz d_12;

			cmp al, ESCAPE_SEQ_4;
			jz d_13;

			jmp d_4;

		d_10:
			movzx eax, word ptr[ecx + edx + 1];
			jmp d_2;

		d_11:
			movzx eax, word ptr[ecx + edx + 1];
			sub eax, SHIFT_2;
			jmp d_2;

		d_12:
			movzx eax, word ptr[ecx + edx + 1];
			add eax, SHIFT_3;
			jmp d_2;

		d_13:
			movzx eax, word ptr[ecx + edx + 1];
			add eax, SHIFT_4;
		
		d_2:
			mov byte ptr[ebp - 0x59], 0;
			add edx, 2;
			movzx eax, ax;

			cmp eax, NO_FONT;
			ja d_3;

			mov eax, NOT_DEF;

		d_3:
			mov[ebp - 0x1C], edx;
			jmp d_5;

		d_4:
			mov[ebp - 0x59], al;
			movzx eax, al;

		d_5:
			push view_end_v28;
			ret;
		}
	}

	uintptr_t view_end_v301;
	__declspec(naked) void view_start_v301()
	{
		__asm {
			mov al, [ecx + edx];

			cmp al, ESCAPE_SEQ_1;
			jz d_10;

			cmp al, ESCAPE_SEQ_2;
			jz d_11;

			cmp al, ESCAPE_SEQ_3;
			jz d_12;

			cmp al, ESCAPE_SEQ_4;
			jz d_13;

			jmp d_4;

		d_10:
			movzx eax, word ptr[ecx + edx + 1];
			jmp d_2;

		d_11:
			movzx eax, word ptr[ecx + edx + 1];
			sub eax, SHIFT_2;
			jmp d_2;

		d_12:
			movzx eax, word ptr[ecx + edx + 1];
			add eax, SHIFT_3;
			jmp d_2;

		d_13:
			movzx eax, word ptr[ecx + edx + 1];
			add eax, SHIFT_4;

		d_2:
			mov byte ptr[ebp - 0x55], 0;
			add edx, 2;
			movzx eax, ax;

			cmp eax, NO_FONT;
			ja d_3;

			mov eax, NOT_DEF;

		d_3:
			mov[ebp - 0x1C], edx;
			jmp d_5;

		d_4:
			mov[ebp - 0x55], al;
			movzx eax, al;

		d_5:
			push view_end_v301;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t view_hook(RunOptions *options) {
		std::string desc = "view";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
			// mov al, byte_XXXXXX[edx]
			byte_pattern::temp_instance().find_pattern("8A 82 ? ? ? ? 88 45 A7 0F B6");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// movをleaにしている
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0), 0x8D, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(1), 0x0D, true);

				// mov [ebp-59h],al
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(6), view_start_v28);
				// mov ecx,[esi + eax*4+0A4h]
				view_end_v28 = byte_pattern::temp_instance().get_first().address(12);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_X:
			// mov al, byte_XXXXXX[edx]
			byte_pattern::temp_instance().find_pattern("8A 82 ? ? ? ? 88 45 AB 0F B6");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// movをleaにしている
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0), 0x8D, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(1), 0x0D, true);

				// mov [ebp-55h],al
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(6), view_start_v301);

				// mov ecx,[esi + eax*4+0A4h]
				view_end_v301 = byte_pattern::temp_instance().get_first().address(12);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("main text");

		// fontOffset
		switch (options->version) {
		case v2_8_X:
			fontOffset = 0x8C;
			break;
		case v3_0_X:
			fontOffset = 0xA4;
			break;
		}

		// スタックサイズ変更
		result |= stackSizeChange_hook(options);
		// バッファアドレス取得
		result |= prepareBuffCopy_hook(options);
		// バッファからバッファにテキストを１文字づつコピー
		result |= func1_hook(options);
		// フォントデータからグリフを取り出して幅チェック処理？に渡す
		result |= func2_hook(options);
		// 強制改行するかしないかの判断
		result |= func3_hook(options);
		// フォントデータからグリフを取り出して表示処理に渡す
		result |= view_hook(options);

		return result;
	}
}