#include "stdinc.h"
#include "byte_pattern.h"

namespace Input {

	/*-----------------------------------------------*/
	
	// TODO: これらダミー関数は必要なかった（直接callして呼べる）
	uintptr_t xx_end;
	uintptr_t xx_end2;
	__declspec(naked) void heap_alloc_f1() {
		__asm {
			nop;
			nop;
			nop;
			add eax, 1;
		}
	}
	__declspec(naked) void heap_free_f1() {
		__asm {
			nop;
			nop;
			nop;
			add eax, 2;
		}
	}
	__declspec(naked) void PHYSFS_utf8ToUcs2_f1() {
		__asm {
			nop;
			nop;
			nop;
			add eax, 3;
		}
	}
	__declspec(naked) void sub_122FEC0_f1() {
		__asm {
			nop;
			nop;
			nop;
			add eax, 4;
		}
	}

	/*-----------------------------------------------*/

	__declspec(naked) void xx_start()
	{
		__asm {
			mov ecx, [ebp - 0x64];

			cmp ch, 0;
			jnz xx_1;

			xor esi, esi;
			push xx_end;
			ret;

		xx_1:
			push 0xFF;	/* dwBytes */
			call heap_alloc_f1;
			pop ecx;

			test eax, eax;
			jz xx_1;
			
			push 0;
			push 0xFF;
			lea eax, [eax];
			mov[ebp - 0x74], eax;
			push eax;
			lea ecx, [ebp - 0x64];
			push ecx;
			call PHYSFS_utf8ToUcs2_f1;
			add esp, 0x10;

			push 0xFF; /* dwBytes */
			call heap_alloc_f1;
			pop ecx;

			/* push */
			push edi;
			push ebx;

			xor edi, edi;
			mov[ebp - 0x78], eax;

			xor esi, esi;

		xx_2:
			mov eax, [ebp - 0x74];
			movzx ax, word ptr[eax + esi];

			// 終了
			cmp ax, 0;
			jz xx_10;

			// 2バイトじゃない
			cmp ah, 0;
			jz xx_2_1;

			xor ecx, ecx;
			mov ecx, ESCAPE_SEQ_1;

			cmp ah, 0xA4;
			jz xx_4;

			cmp ah, 0xA3;
			jz xx_4;

			cmp ah, 0xA7;
			jz xx_4;

			cmp ah, 0x24;
			jz xx_4;

			cmp ah, 0x5B;
			jz xx_4;

			cmp ah, 0x0;
			jz xx_4;

			cmp ah, 0x5C;
			jz xx_4;

			cmp ah, 0x20;
			jz xx_4;

			cmp ah, 0x0D;
			jz xx_4;

			cmp ah, 0x0A;
			jz xx_4;

			cmp ah, 0x22;
			jz xx_4;

			cmp ah, 0x7B;
			jz xx_4;

			cmp ah, 0x7D;
			jz xx_4;

			cmp ah, 0x40;
			jz xx_4;

			cmp ah, 0x3B;
			jz xx_4;

			cmp ah, 0x80;
			jz xx_4;

			cmp ah, 0x7E;
			jz xx_4;

			cmp ah, 0xBD;
			jz xx_4;

			cmp ah, 0x5F;
			jnz xx_3;

		xx_4:
			add ecx, 2;

		xx_3:
			cmp al, 0xA4;
			jz xx_5;

			cmp al, 0xA3;
			jz xx_5;

			cmp al, 0xA7;
			jz xx_5;

			cmp al, 0x24;
			jz xx_5;

			cmp al, 0x5B;
			jz xx_5;

			cmp al, 0x0;
			jz xx_5;

			cmp al, 0x5C;
			jz xx_5;

			cmp al, 0x20;
			jz xx_5;

			cmp al, 0x0D;
			jz xx_5;

			cmp al, 0x0A;
			jz xx_5;

			cmp al, 0x22;
			jz xx_5;

			cmp al, 0x7B;
			jz xx_5;

			cmp al, 0x7D;
			jz xx_5;

			cmp al, 0x40;
			jz xx_5;

			cmp al, 0x3B;
			jz xx_5;

			cmp al, 0x80;
			jz xx_5;

			cmp al, 0x7E;
			jz xx_5;

			cmp al, 0xBD;
			jz xx_5;

			cmp al, 0x5F;
			jnz xx_6;

		xx_5:
			add ecx, 1;

		xx_6:
			cmp ecx, ESCAPE_SEQ_2;
			jnz xx_6_1;
			add al, LOW_SHIFT;
			jmp xx_7;

		xx_6_1:
			cmp ecx, ESCAPE_SEQ_3;
			jnz xx_6_2;
			sub ah, HIGH_SHIFT;
			jmp xx_7;

		xx_6_2:
			cmp ecx, ESCAPE_SEQ_4;
			jnz xx_7;
			add al, LOW_SHIFT;
			sub ah, HIGH_SHIFT;
		
		xx_7:
			add esi, 2;
			mov ebx, [ebp - 0x78];
			mov[ebx + edi], cl;
			mov[ebx + edi + 1], ax;
			add edi, 3;

			jmp xx_2;

		xx_2_1:
			inc esi;
			mov ebx, [ebp - 0x78];
			mov byte ptr [ebx + edi], al;
			inc edi;

			jmp xx_2;

		/* LOOP END */

		xx_10:
			/* pop */
			pop ebx;
			pop edi;

			/* count */
			xor esi, esi;

		xx_12:
			mov ecx, [ebp - 0x78];
			movzx ecx,byte ptr [ecx + esi];

			cmp cl, 0;
			jz xx_13;

			/*  edi */
			/* eax, esi, ecx */

			lea eax, [ebp - 0x1C];
			mov[ebp - 0x1C], ecx;
			mov edx, [edi];
			lea ecx, [ebp - 0x38];
			push eax;
			mov[ebp - 0x18], 1;
			call sub_122FEC0_f1;
			push eax;
			mov ecx, edi;
			mov edx,[edi];
			call dword ptr[edx + 0x28];

			inc esi;
			jmp xx_12;

		xx_13:

			push[ebp - 0x74];
			call heap_free_f1;

			push[ebp - 0x78];
			call heap_free_f1;

			pop ecx;
			pop ecx;

			push xx_end2;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t input_hook(RunOptions *options) {
		std::string desc = "input";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
			byte_pattern::temp_instance().find_pattern("55 8B EC 83 EC 70 53 56 57 8B F9 8B DA");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(5), 0x78, true);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("8A 4D 9C 33 F6 80 F9 80");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), xx_start);
				xx_end = byte_pattern::temp_instance().get_first().address(5);
			}
			else return CK2ERROR1;

			switch (options->version) {
			case v3_1_0:
			case v3_1_1:
				byte_pattern::temp_instance().find_pattern("FF 75 A0 E8 ? ? ? ? 8B D0 83 C4 04");
				if (byte_pattern::temp_instance().has_size(1, desc)) {
					xx_end2 = byte_pattern::temp_instance().get_first().address();
				}
				else return CK2ERROR1;
				break;
			default:
				byte_pattern::temp_instance().find_pattern("FF 75 A0 E8 ? ? ? ? 83 C4 04 25");
				if (byte_pattern::temp_instance().has_size(1, desc)) {
					xx_end2 = byte_pattern::temp_instance().get_first().address();
				}
				else return CK2ERROR1;
				break;
			}

			// same as sub_16FEEFB
			byte_pattern::temp_instance().find_pattern("8B FF 55 8B EC 56 8B 75 08 83 FE E0");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(heap_alloc_f1, byte_pattern::temp_instance().get_first().address());
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("8B FF 55 8B EC 83 7D 08 00 74 2D FF 75");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(heap_free_f1, byte_pattern::temp_instance().get_first().address());
			}
			else return CK2ERROR1;

			// PHYSFS_utf8ToUcs2
			byte_pattern::temp_instance().find_pattern("55 8B EC 51 8B 4D 10 53");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(PHYSFS_utf8ToUcs2_f1, byte_pattern::temp_instance().get_first().address());
			}
			else return CK2ERROR1;

			// struct init
			byte_pattern::temp_instance().find_pattern("C7 41 08 01 00 00 00 C7 41 0C 00 00 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(sub_122FEC0_f1, byte_pattern::temp_instance().get_first().address(-0x12));
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t loc_172DEE2;
	__declspec(naked) void yy_1() {
		__asm {
			// store reg / counter
			push esi;
			xor esi, esi;

			mov eax, [edi + 0x28]; // 文字列長さ
			
			lea ecx, [edi + 0x18]; // テキスト

			cmp eax, 0x10;
			jbe yy_2;

			mov ecx, [ecx];

		yy_2:
			mov eax, [edi + 0x34]; // キャレット位置
			sub eax, 3;
			js yy_3;
			mov al, [ecx + eax];

			cmp al, ESCAPE_SEQ_1;
			jz yy_4;

			cmp al, ESCAPE_SEQ_2;
			jz yy_4;

			cmp al, ESCAPE_SEQ_3;
			jz yy_4;

			cmp al, ESCAPE_SEQ_4;
			jnz yy_3;

		yy_4:
			mov esi, 2;

		yy_3:
			mov eax, [edi];
			mov ecx, edi;

			test bl, bl;
			jnz yy_6;

			call dword ptr[eax + 0xA0];
			jmp yy_5;

		yy_6:
			call dword ptr[eax + 0x9C];

		yy_5:
			cmp esi, 0;
			jz yy_7;

			sub esi, 1;
			jmp yy_3;

		yy_7:
			// restore reg / counter
			pop esi;

			pop ebx;

			push loc_172DEE2;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t backSpace_hook(RunOptions *options) {
		std::string desc = "backspace";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
		case v3_1_1:
			byte_pattern::temp_instance().find_pattern("8B 07 84 DB 5B 8B CF");
			if (byte_pattern::temp_instance().has_size(1,desc + " start" )) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), yy_1);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("0F B7 47 36 8B CF 50 8D 45 DC 50");
			if (byte_pattern::temp_instance().has_size(2, desc + " end")) { // select first !
				loc_172DEE2 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("input");

		// inputの修正
		result |= input_hook(options);

		// backspaceの修正
		result |= backSpace_hook(options);

		return result;
	}
}