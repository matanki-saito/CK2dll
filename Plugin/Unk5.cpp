#include "stdinc.h"
#include "byte_pattern.h"


namespace Unk5 {

	uintptr_t j_7;
	__declspec(naked) void j_1()
	{
		__asm {
			cmp byte ptr[eax + ecx], ESCAPE_SEQ_1;
			jz m_10;

			cmp byte ptr[eax + ecx], ESCAPE_SEQ_2;
			jz m_11;

			cmp byte ptr[eax + ecx], ESCAPE_SEQ_3;
			jz m_12;

			cmp byte ptr[eax + ecx], ESCAPE_SEQ_4;
			jz m_13;

			jmp m_3;

		m_10:
			movzx eax, word ptr[eax + ecx + 1];
			jmp m_1x;

		m_11:
			movzx eax, word ptr[eax + ecx + 1];
			sub eax, SHIFT_2;
			jmp m_1x;

		m_12:
			movzx eax, word ptr[eax + ecx + 1];
			add eax, SHIFT_3;
			jmp m_1x;

		m_13:
			movzx eax, word ptr[eax + ecx + 1];
			add eax, SHIFT_4;

		m_1x:
			add ecx, 2;
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja m_4;
			mov eax, NOT_DEF;
			jmp m_4;

		m_3:
			movzx eax, byte ptr[eax + ecx];

		m_4:
			mov     eax, [edi + eax * 4 + 0xA4];

			push j_7;
			ret;
		}
	}


	/*-----------------------------------------------*/

	errno_t fix1_hook(RunOptions *options) {
		std::string desc = "fix1";

		switch (options->version) {
		case v3_0_X:
			byte_pattern::temp_instance().find_pattern("0F B6 04 08 8B 84 87 A4 00 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc + " start")) {
				// movzx   eax, byte ptr [eax+ecx]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), j_1);
				// test    eax, eax
				j_7 = byte_pattern::temp_instance().get_first().address(0xB);
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

		// *4+0A4h‚ÅŒŸõ‚µ‚ÄŒ©‚Â‚©‚Á‚½êŠ
		// ‚Ç‚¤‚¢‚¤ì—p‚ª‚ ‚é‚©‚Í‚í‚©‚ç‚È‚¢
		byte_pattern::debug_output2("unk5");

		result |= fix1_hook(options);

		return result;
	}
}