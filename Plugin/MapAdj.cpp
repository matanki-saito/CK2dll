#include "stdinc.h"
#include "byte_pattern.h"

namespace MapAdj {
	/*-----------------------------------------------*/

	errno_t stackSizeChange_hook(RunOptions *options) {
		std::string desc = "stack size change";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			// sub esp,178h
			byte_pattern::temp_instance().find_pattern("81 EC 78 01 00 00 8B 43 18");
			if (byte_pattern::temp_instance().has_size(1,desc)) {
				injector::WriteMemory<uint8_t>(
					byte_pattern::temp_instance().get_first().address(2),
					0x7A,
					true
				);
			}
			else return CK2ERROR1;
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t m_5;
	__declspec(naked) void m_1()
	{
		__asm {
			cmp byte ptr[eax + edx], ESCAPE_SEQ_1;
			jz m_10;

			cmp byte ptr[eax + edx], ESCAPE_SEQ_2;
			jz m_11;

			cmp byte ptr[eax + edx], ESCAPE_SEQ_3;
			jz m_12;

			cmp byte ptr[eax + edx], ESCAPE_SEQ_4;
			jz m_13;

			jmp m_3;

		m_10:
			movzx eax, word ptr[eax + edx + 1];
			jmp m_1x;

		m_11:
			movzx eax, word ptr[eax + edx + 1];
			sub eax, SHIFT_2;
			jmp m_1x;

		m_12:
			movzx eax, word ptr[eax + edx + 1];
			add eax, SHIFT_3;
			jmp m_1x;

		m_13:
			movzx eax, word ptr[eax + edx + 1];
			add eax, SHIFT_4;

		m_1x:
			add edx, 2;
			mov[ebp - 0x24], edx;
			sub edx, 2;

			movzx eax, ax;
			cmp eax, NO_FONT;
			ja m_4;
			mov eax, NOT_DEF;
			jmp m_4;

		m_3:
			movzx eax, byte ptr[eax + edx];

		m_4:
			mov esi, [esi + eax * 4];

			mov[ebp - 0x172], ax;
			cmp word ptr[ebp - 0x172], 0x100;

			jb m_421;
			cmp word ptr[ebp - 0x1C], 3;

			ja m_421;
			inc edx;
			mov word ptr[ebp - 0x172], 0x10;

		m_421:
			push m_5;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t view_hook(RunOptions *options) {
		std::string desc = "map view";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			// movzx eax,byte ptr [eax+edx]
			byte_pattern::temp_instance().find_pattern("0F B6 04 10 8B 34 86");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), m_1);
				// test esi,esi
				m_5 = byte_pattern::temp_instance().get_first().address(7);
			}
			else return CK2ERROR1;
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t kk_4;
	__declspec(naked) void kk_1() {
		__asm {
			cmp word ptr[ebp - 0x172], 0x100;
			jb kk_2;
			sub eax, 3;
			jmp kk_3;

		kk_2:
			dec eax;

		kk_3:
			sqrtss xmm1, xmm1;

			push kk_4;
			ret;
		}

	};

	/*-----------------------------------------------*/

	errno_t mapAdj1_hook(RunOptions *options) {
		std::string desc = "map adj 1";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			//dec eax
			byte_pattern::temp_instance().find_pattern("48 F3 0F 51 C9 66 0F 6E");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), kk_1);
				kk_4 = byte_pattern::temp_instance().get_first().address(5);
			}
			else return CK2ERROR1;
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t jj_2;
	__declspec(naked) void jj_1() {
		__asm {

			mov eax, [ebp - 0x0B4];
			mov esi, [ebx + 0x38];
			mov edx, [ebp - 0x24];
			inc edx;

			push jj_2;
			ret;
		}
	};

	/*-----------------------------------------------*/

	errno_t mapAdj2_hook(RunOptions *options) {
		std::string desc = "map adj 2";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			// mov eax, [ebp-0B4h]
			byte_pattern::temp_instance().find_pattern("8B 85 4C FF FF FF 8B 73");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// inc edx
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(-0xE), 0x90, true);
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), jj_1);
				// mov edx,ecx
				jj_2 = byte_pattern::temp_instance().get_first().address(9);
			}
			else return CK2ERROR1;
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t stackClear_hook(RunOptions *options) {
		std::string desc = "stack clear";

		switch (options->version){
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
			// lea esp,[ebp-180h]
			byte_pattern::temp_instance().find_pattern("8D A5 80 FE FF FF 5F");
			if (byte_pattern::temp_instance().has_size(1,desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x7E, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("map font adjust 1");

		// M用にスタック修正
		result |= stackSizeChange_hook(options);
		// マップフォント表示処理
		result |= view_hook(options);
		//マップテキストの表示位置調整
		result |= mapAdj1_hook(options);
		//マップフォントの位置調整
		result |= mapAdj2_hook(options);
		// スタック後始末
		result |= stackClear_hook(options);

		return result;
	}
}