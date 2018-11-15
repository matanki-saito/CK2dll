#include "stdinc.h"
#include "byte_pattern.h"


namespace NickNameFix
{
	/*-----------------------------------------------*/

	uintptr_t issue_14_end_1;
	__declspec(naked) void issue_14_start_1() {
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
			push issue_14_end_1;
			ret;
		}
	}

	/*-----------------------------------------------*/

	uintptr_t issue_14_end_2;
	__declspec(naked) void issue_14_start_2() {
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
			push issue_14_end_2;
			ret;
		}
	}

	/*-----------------------------------------------*/

	uintptr_t issue_14_end_3;
	__declspec(naked) void issue_14_start_3() {
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
			push issue_14_end_3;
			ret;
		}
	}

	/*-----------------------------------------------*/

	uintptr_t issue_14_end_4;
	__declspec(naked) void issue_14_start_4() {
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
			push issue_14_end_4;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix1_hook(CK2Version version) {
		std::string desc = "nickname order fix";

		switch (version) {
		case v2_8_X:
			/* [Title] [FirstName] [NickName]となるのを[NickName] [FirstName] [Title] にする issue-14 */
			byte_pattern::temp_instance().find_pattern("8D 45 84 C6 45 FC 11 50 8D 85 08");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_14_start_1);
				issue_14_end_1 = byte_pattern::temp_instance().get_first().address(0x12);
	
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x17), issue_14_start_2);
				issue_14_end_2 = byte_pattern::temp_instance().get_first().address(0x28);
	
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x2D), issue_14_start_3);
				issue_14_end_3 = byte_pattern::temp_instance().get_first().address(0x3E);
	
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x43), issue_14_start_4);
				issue_14_end_4 = byte_pattern::temp_instance().get_first().address(0x57);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_X:
			/* [Title] [FirstName] [NickName]となるのを[NickName] [FirstName] [Title] にする issue-14 */
			byte_pattern::temp_instance().find_pattern("8D 45 84 C6 45 FC 11 50 8D 85 08");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_14_start_1);
				issue_14_end_1 = byte_pattern::temp_instance().get_first().address(0x12);

				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x17), issue_14_start_2);
				issue_14_end_2 = byte_pattern::temp_instance().get_first().address(0x28);

				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x2D), issue_14_start_3);
				issue_14_end_3 = byte_pattern::temp_instance().get_first().address(0x3E);

				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x43), issue_14_start_4);
				issue_14_end_4 = byte_pattern::temp_instance().get_first().address(0x57);
			}
			else return CK2ERROR1;
			return NOERROR;

		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(CK2Version version) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("nickname order fix");

		result |= fix1_hook(version);

		return result;
	}
}