#include "stdinc.h"
#include "byte_pattern.h"


namespace NickNameFix
{
	/*-----------------------------------------------*/

	uintptr_t func1_v30;

	/*-----------------------------------------------*/

	errno_t func_hook(RunOptions *options) {
		std::string desc = "func hook";

		switch (options->version) {
		case v2_8_X:
			/* 使わない */
			return NOERROR;
		case v3_0_X:
			// push [ebp+arg_4]
			byte_pattern::temp_instance().find_pattern("FF 75 0C 8D 45 D8 C7 45 F0 00 00 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// 先頭
				// push ebp
				func1_v30 = byte_pattern::temp_instance().get_first().address(-0x1C);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t issue_14_end_1_v28;
	__declspec(naked) void issue_14_start_1_v28() {
		__asm {
			mov     ebx, [edi + 0x9C];
			add     ebx, 0xC;

			cmp [ebx], 0x10;
			jz issue_14_true;
			cmp [ebx], 0x11;
			jz issue_14_true;
			cmp [eax], 0x12;
			jz issue_14_true;
			cmp [ebx], 0x13;
			jz issue_14_true;

			xor ebx, ebx;
			jmp issue_14_x;

		issue_14_true:
			mov ebx, 1;

		issue_14_x:
			cmp ebx, 1;
			jz issue_14_1_fix;

		issue_14_1_org:
			// Titleにspaceを追加
			lea     eax, [ebp - 0x7C]; // joinedSrc ([space])
			mov     byte ptr[ebp - 0x4], 0x11; // profile cnt ?
			push    eax;
			lea     eax, [ebp - 0xF8]; // dest
			push    eax;
			lea     ecx, [ebp - 0x34];  // orgSrc (title)
			jmp issue_14_1_ret;

		issue_14_1_fix:
			// あだ名にFirstNameを追加
			lea     eax, [ebp - 0x98]; // joinedSrc ([space])
			mov     byte ptr[ebp - 0x4], 0x11; // profile cnt ?
			push    eax;
			lea     eax, [ebp - 0xF8]; // dest
			push    eax;
			mov     ecx, [edi + 0x9C];
			add     ecx, 0xC;

		issue_14_1_ret:
			push issue_14_end_1_v28;
			ret;
		}
	}

	uintptr_t issue_14_end_2_v28;
	__declspec(naked) void issue_14_start_2_v28() {
		__asm {
			cmp ebx, 1;
			jz issue_14_2_fix;

		issue_14_2_org:
			//  Title+spaceにFirstNameを追加
			lea     ecx, [ebp - 0x98]; // joinedSrc
			mov     byte ptr[ebp - 0x4], 0x12; // profile cnt ?
			push    ecx;
			lea     ecx, [ebp - 0x4C]; // dest
			push    ecx;
			mov     ecx, eax; // orgSrc
			jmp issue_14_2_ret;

		issue_14_2_fix:
			// あだ名+FirstNameにスペースを追加
			lea     ecx, [ebp - 0x7C]; // joinedSrc
			mov     byte ptr[ebp - 0x4], 0x12; // profile cnt ?
			push    ecx;
			lea     ecx, [ebp - 0x4C]; // dest
			push    ecx;
			mov     ecx, eax; // orgSrc

		issue_14_2_ret:
			push issue_14_end_2_v28;
			ret;
		}
	}

	uintptr_t issue_14_end_3_v28;
	__declspec(naked) void issue_14_start_3_v28() {
		__asm {
			cmp ebx, 1;
			jz issue_14_3_fix;

		issue_14_3_org:
			// Title+space+FirstNameにスペースを追加
			lea     ecx, [ebp - 0xC8];  // joinedSrc
			mov     byte ptr[ebp - 0x4], 0x13; // profile cnt ?
			push    ecx;
			lea     ecx, [ebp - 0x64]; // dest
			push    ecx;
			mov     ecx, eax;  // orgSrc
			jmp issue_14_3_ret;

		issue_14_3_fix:
			// あだ名+FirstName+spaceにTitleを追加
			lea     ecx, [ebp - 0x34];  // joinedSrc
			mov     byte ptr[ebp - 0x4], 0x13; // profile cnt ?
			push    ecx;
			lea     ecx, [ebp - 0x64]; // dest
			push    ecx;
			mov     ecx, eax;  // orgSrc

		issue_14_3_ret:
			push issue_14_end_3_v28;
			ret;
		}
	}

	uintptr_t issue_14_end_4_v28;
	__declspec(naked) void issue_14_start_4_v28() {
		__asm {
			cmp ebx, 1;
			jz issue_14_4_fix;

		issue_14_end_4:
			// あだ名
			mov     esi, [ebp + 0x8]; // arg_0, dest
			mov     byte ptr[ebp - 0x4], 0x14; // prifile cnt ?
			mov     ecx, [edi + 0x9C];
			add     ecx, 0xC;
			push    ecx; // joinedSrc
			push    esi;
			mov     ecx, eax;  // orgSrc
			jmp issue_14_4_ret;
			
		issue_14_4_fix:
			//  あだ名+FirstName+space+Titleにスペースを追加
			mov     esi, [ebp + 0x8]; // arg_0, dest
			mov     byte ptr[ebp - 0x4], 0x14; // prifile cnt ?
			lea     ecx, [ebp - 0xC8]; // joinedSrc
			push    ecx;
			push    esi;
			mov     ecx, eax;  // orgSrc

		issue_14_4_ret:
			push issue_14_end_4_v28;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix1_hook(RunOptions *options) {
		std::string desc = "nickname order fix";

		switch (options->version) {
		case v2_8_X:
			/* [Title] [FirstName] [NickName]となるのを[NickName] [FirstName] [Title] にする issue-14 */
			byte_pattern::temp_instance().find_pattern("8D 45 84 C6 45 FC 11 50 8D 85 08");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_14_start_1_v28);
				issue_14_end_1_v28 = byte_pattern::temp_instance().get_first().address(0x12);
	
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x17), issue_14_start_2_v28);
				issue_14_end_2_v28 = byte_pattern::temp_instance().get_first().address(0x28);
	
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x2D), issue_14_start_3_v28);
				issue_14_end_3_v28 = byte_pattern::temp_instance().get_first().address(0x3E);
	
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x43), issue_14_start_4_v28);
				issue_14_end_4_v28 = byte_pattern::temp_instance().get_first().address(0x57);
			}
			else return CK2ERROR1;
			return NOERROR;
		case v3_0_0:
		case v3_0_X:
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t issue_14_end_R_v30;
	__declspec(naked) void issue_14_start_NICKNAME_FIRSTNAME_TITLE_R_v30() {
		__asm {
			// [ebp - 0x30] : [space]
			// [edi + 0x7C] + 0xC : [NickName]
			// [ebp - 0x48] : [Title]
			// [ebp - 0xC4] : [space]
			// [ebp - 0x94] : [FirstName]
			// [ebp + 0x8] : retrun arg_0

			lea     eax, [ebp - 0xC4]; // [space]
			mov     byte ptr[ebp - 0x4], 0x16;
			push    eax;
			lea     eax, [ebp - 0x64]; // buf
			push    eax;
			mov     ecx, [edi + 0x7C]; // [NickName]
			add     ecx, 0xC;
			
			call    func1_v30;

			lea     ecx, [ebp - 0x94]; // [FirstName]
			mov     byte ptr[ebp - 0x4], 0x17;
			push    ecx;
			lea     ecx, [ebp -0x7C]; // buf
			push    ecx;
			mov     ecx, eax;
			call    func1_v30;

			lea     ecx, [ebp - 0x30]; // [space]
			mov     byte ptr[ebp - 0x4], 0x18;
			push    ecx;
			lea     ecx, [ebp - 0xDC]; // buf
			push    ecx;
			mov     ecx, eax;
			call    func1_v30;

			mov     esi, [ebp + 0x8]; // retrun arg_0
			mov     byte ptr[ebp - 0x4], 0x19;
			lea     ecx, [ebp - 0x48]; // [Title]
			push    ecx;
			push    esi;
			mov     ecx, eax;
			call    func1_v30;

			push issue_14_end_R_v30;
			ret;
		}
	}
	__declspec(naked) void issue_14_start_FIRSTNAME_NICKNAME_TITLE_R_v30() {
		__asm {
			// [ebp - 0x30] : [space]
			// [edi + 0x7C] + 0xC : [NickName]
			// [ebp - 0x48] : [Title]
			// [ebp - 0xC4] : [space]
			// [ebp - 0x94] : [FirstName]
			// [ebp + 0x8] : retrun arg_0

			lea     eax, [ebp - 0xC4]; // [space]
			mov     byte ptr[ebp - 0x4], 0x16;
			push    eax;
			lea     eax, [ebp - 0x64]; // buf
			push    eax;
			lea     ecx, [ebp - 0x94]; // [FirstName]
			call    func1_v30;

			mov     ecx, [edi + 0x7C]; // [NickName]
			add     ecx, 0xC;
			mov     byte ptr[ebp - 0x4], 0x17;
			push    ecx;
			lea     ecx, [ebp - 0x7C]; // buf
			push    ecx;
			mov     ecx, eax;
			call    func1_v30;
			
			lea     ecx, [ebp - 0x30]; // [space]
			mov     byte ptr[ebp - 0x4], 0x18;
			push    ecx;
			lea     ecx, [ebp - 0xDC]; // buf
			push    ecx;
			mov     ecx, eax;
			call    func1_v30;
			
			mov     esi, [ebp + 0x8]; // retrun arg_0
			mov     byte ptr[ebp - 0x4], 0x19;
			lea     ecx, [ebp - 0x48]; // [Title]
			push    ecx;
			push    esi;
			mov     ecx, eax;
			call    func1_v30;

			push issue_14_end_R_v30;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fixR_hook(RunOptions *options) {
		std::string desc = "nickname order fix R";

		void * start;
		switch (options->nickNameOrder) {
		case NickNameOrder::NICKNAME_FIRSTNAME_TITLE:
			start = issue_14_start_NICKNAME_FIRSTNAME_TITLE_R_v30;
			break;
		case NickNameOrder::FIRSTNAME_NICKNAME_TITLE:
			start = issue_14_start_FIRSTNAME_NICKNAME_TITLE_R_v30;
			break;
		default:
			return CK2ERROR1;
		}

		switch (options->version) {
		case v2_8_X:
			return NOERROR;
		case v3_0_0:
			// lea ecx,[ebp+var_DC]
			byte_pattern::temp_instance().find_pattern("8D 8D 24 FF FF FF E8 11 86 EF FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// lea eax,[ebp+var_C4]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(-0x59), start);
				
				issue_14_end_R_v30 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;
			return NOERROR;
		case v3_0_X:
			// lea ecx,[ebp+var_DC]
			byte_pattern::temp_instance().find_pattern("8D 8D 24 FF FF FF E8 F1 8A EF FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// lea eax,[ebp+var_C4]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(-0x59), start);
				
				issue_14_end_R_v30 = byte_pattern::temp_instance().get_first().address();
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t issue_14_end_L_v30;
	__declspec(naked) void issue_14_NICKNAME_FIRSTNAME_TITLE_L_v30() {
		__asm {
			// [ebp - 0x30] : [space]
			// [edi + 0x7C] + 0xC : [NickName]
			// [ebp - 0x48] : [Title]
			// [ebp - 0xC4] : [space]
			// [ebp - 0x94] : [FirstName]
			// [ebp + 0x8] : retrun arg_0

			lea     eax, [ebp - 0x30]; // [space]
			mov     byte ptr[ebp - 4], 0x11;
			push    eax;
			lea     eax, [ebp - 0xDC]; // [buf]
			push    eax;
			lea     ecx, [ebp - 0x94]; // [FirstName]
			call    func1_v30;

			lea     ecx, [ebp - 0x48]; // [Title]
			mov     byte ptr[ebp - 4], 0x12;
			push    ecx;
			lea     ecx, [ebp - 0x64]; // [buf]
			push    ecx;
			mov     ecx, eax;
			call    func1_v30;

			lea     ecx, [ebp - 0xC4]; // [space]
			mov     byte ptr[ebp - 4], 0x13;
			push    ecx;
			lea     ecx, [ebp - 0x7C]; // [buf]
			push    ecx;
			mov     ecx, eax;
			call    func1_v30;

			mov     esi, [ebp + 0x8]; // retrun arg_0
			mov     ecx, [edi + 0x7C]; // [NickName]
			add     ecx, 0xC;
			push    ecx;
			push    esi;
			mov     ecx, eax;
			mov     byte ptr[ebp - 4], 0x14;
			call    func1_v30;

			push issue_14_end_L_v30;
			ret;
		}
	}
	__declspec(naked) void issue_14_FIRSTNAME_NICKNAME_TITLE_L_v30() {
		__asm {
			// [ebp - 0x30] : [space]
			// [edi + 0x7C] + 0xC : [Title]
			// [ebp - 0x48] : [FirstName]
			// [ebp - 0xC4] : [space]
			// [ebp - 0x94] : [NickName]
			// [ebp + 0x8] : retrun arg_0

			lea     eax, [ebp - 0x30]; // [space]
			mov     byte ptr[ebp - 4], 0x11;
			push    eax;
			lea     eax, [ebp - 0xDC]; // [buf]
			push    eax;
			lea     ecx, [ebp - 0x48]; // [FirstName]
			call    func1_v30;

			lea     ecx, [ebp - 0x94]; // [NickName]
			mov     byte ptr[ebp - 4], 0x12;
			push    ecx;
			lea     ecx, [ebp - 0x64]; // [buf]
			push    ecx;
			mov     ecx, eax;
			call    func1_v30;

			lea     ecx, [ebp - 0xC4]; // [space]
			mov     byte ptr[ebp - 4], 0x13;
			push    ecx;
			lea     ecx, [ebp - 0x7C]; // [buf]
			push    ecx;
			mov     ecx, eax;
			call    func1_v30;

			mov     esi, [ebp + 0x8]; // retrun arg_0
			mov     ecx, [edi + 0x7C]; // [Title]
			add     ecx, 0xC;
			push    ecx;
			push    esi;
			mov     ecx, eax;
			mov     byte ptr[ebp - 4], 0x14;
			call    func1_v30;

			push issue_14_end_L_v30;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fixL_hook(RunOptions *options) {
		std::string desc = "nickname order fix L";

		void * start;
		switch (options->nickNameOrder) {
		case NickNameOrder::NICKNAME_FIRSTNAME_TITLE:
			start = issue_14_NICKNAME_FIRSTNAME_TITLE_L_v30;
			break;
		case NickNameOrder::FIRSTNAME_NICKNAME_TITLE:
			start = issue_14_FIRSTNAME_NICKNAME_TITLE_L_v30;
			break;
		default:
			return CK2ERROR1;
		}

		switch (options->version) {
		case v2_8_X:
			return NOERROR;
		case v3_0_X:
			// lea eax,[ebp+var_30]
			byte_pattern::temp_instance().find_pattern("8D 45 D0 C6 45 FC 11 8B 4F 7C 50 8D 85");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), start);
				// lea ecx,[ebp+var_7C]
				issue_14_end_L_v30 = byte_pattern::temp_instance().get_first().address(0x59);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = NOERROR;

		if (options->nickNameOrder != NickNameOrder::DISABLE) {
			byte_pattern::debug_output2("nickname order fix");

			result |= func_hook(options);

			// v28のみ legacy
			result |= fix1_hook(options);

			// v30のみ
			// https://github.com/matanki-saito/CK2dll/issues/46
			result |= fixR_hook(options);
			
			// https://github.com/matanki-saito/CK2dll/issues/46
			//result |= fixL_hook(options);

		}

		return result;
	}
}