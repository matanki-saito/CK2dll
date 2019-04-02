#include "stdinc.h"
#include "byte_pattern.h"

namespace FileSave {

	/*-----------------------------------------------*/
	
	errno_t fileNameSaftySkip_hook(RunOptions *options) {
		std::string desc = "file name safty skip";

		switch (options->version) {
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
			// xor edx,edx (33 D2)
			byte_pattern::temp_instance().find_pattern("33 D2 85 FF 0F 8E EE 00 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// test edi,edi (85 FF) -> jmp (E9)
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x3), 0xE9, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x4), 0xFE, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x5), 0x00, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x6), 0x00, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x7), 0x00, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		case v2_8_X:
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t fileNameSaftySkip2_hook(RunOptions *options) {
		std::string desc = "file name safty skip 2";

		switch (options->version) {
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
			// push ebx
			byte_pattern::temp_instance().find_pattern("53 8B 59 10 56 33 F6 85 DB");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// test ebx,ebx
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x7), 0xE9, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x8), 0xC4, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x9), 0x02, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0xA), 0x00, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0xB), 0x00, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		case v2_8_X:
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t PHYSFS_utf8FromUcs2;
	errno_t PHYSFS_utf8FromUcs2_hook(RunOptions *options) {
		std::string desc = "get PHYSFS_utf8FromUcs2 addr";

		switch (options->version) {
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
			// 0: latin1
			// 1: ucs2
			// 2: ucs4
			byte_pattern::temp_instance().find_pattern("55 8B EC 56 8B 75 10 8B C6 57 8B 7D");
			if (byte_pattern::temp_instance().has_size(3, desc)) {
				PHYSFS_utf8FromUcs2 = byte_pattern::temp_instance().get(1).address();
			}
			else return CK2ERROR1;
			return NOERROR;
		case v2_8_X:
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t filenameEncode_v300_end;
	uintptr_t filenameEncode_v310_end;
	wchar_t fnamew[200] = {};
	char fnameutf8[200] = {};
	uintptr_t buff;

	void rstTmpMem() {
		memset(fnamew, '\0', sizeof(wchar_t) * 200);
		memset(fnameutf8, '\0', sizeof(char) * 200);
	}

	__declspec(naked) void filenameEncode_v300_start() {
		__asm {
			push eax;

			call rstTmpMem;

			lea ecx, dword ptr [ebp - 0x88];
			cmp dword ptr[ecx + 0x14], 0x10;
			jb A;
			mov ecx, [ecx];
		A:
			mov buff, ecx;

			push edx;
			push ebx;
			push esi;
			xor esi, esi;

		issue_7_1_loop_start:
			cmp byte ptr[ecx], ESCAPE_SEQ_1;
			jz issue_7_1_10;
			cmp byte ptr[ecx], ESCAPE_SEQ_2;
			jz issue_7_1_11;
			cmp byte ptr[ecx], ESCAPE_SEQ_3;
			jz issue_7_1_12;
			cmp byte ptr[ecx], ESCAPE_SEQ_4;
			jz issue_7_1_13;
			cmp byte ptr[ecx], NULL;
			jz issue_7_1_loop_end;

			movzx eax, byte ptr[ecx];
			jmp issue_7_1_yy;

		issue_7_1_10:
			movzx eax, word ptr[ecx + 1];
			jmp issue_7_1_xx;

		issue_7_1_11:
			movzx eax, word ptr[ecx + 1];
			sub eax, SHIFT_2;
			jmp issue_7_1_xx;

		issue_7_1_12:
			movzx eax, word ptr[ecx + 1];
			add eax, SHIFT_3;
			jmp issue_7_1_xx;

		issue_7_1_13:
			movzx eax, word ptr[ecx + 1];
			add eax, SHIFT_4;

		issue_7_1_xx:
			add ecx, 2;

		issue_7_1_yy:
			mov word ptr[fnamew + esi], ax;
			inc ecx;
			add esi, 2;
			jmp issue_7_1_loop_start;

		issue_7_1_loop_end:
			push 0; // ?
			push 200; // dst-buf-len 
			push buff; // dst
			lea eax, fnamew; // src
			push eax;
			call PHYSFS_utf8FromUcs2;
			add esp, 0x10;

			lea ecx, dword ptr[ebp - 0x88];
			//mov dword ptr[ecx + 0x10], esi;
			//mov dword ptr[ecx + 0x14], 0x10;

			pop esi;
			pop ebx;
			pop edx;

			push filenameEncode_v300_end;
			ret;
		}
	}

	__declspec(naked) void filenameEncode_v310_start() {
		__asm {
			push eax;

			call rstTmpMem;

			lea ecx, dword ptr[ebp - 0x88];
			cmp dword ptr[ecx + 0x14], 0x10;
			jb A;
			mov ecx, [ecx];
		A:
			mov buff, ecx;

			push edx;
			push ebx;
			push esi;
			xor esi, esi;

		issue_7_1_loop_start:
			cmp byte ptr[ecx], ESCAPE_SEQ_1;
			jz issue_7_1_10;
			cmp byte ptr[ecx], ESCAPE_SEQ_2;
			jz issue_7_1_11;
			cmp byte ptr[ecx], ESCAPE_SEQ_3;
			jz issue_7_1_12;
			cmp byte ptr[ecx], ESCAPE_SEQ_4;
			jz issue_7_1_13;
			cmp byte ptr[ecx], NULL;
			jz issue_7_1_loop_end;

			movzx eax, byte ptr[ecx];
			jmp issue_7_1_yy;

		issue_7_1_10:
			movzx eax, word ptr[ecx + 1];
			jmp issue_7_1_xx;

		issue_7_1_11:
			movzx eax, word ptr[ecx + 1];
			sub eax, SHIFT_2;
			jmp issue_7_1_xx;

		issue_7_1_12:
			movzx eax, word ptr[ecx + 1];
			add eax, SHIFT_3;
			jmp issue_7_1_xx;

		issue_7_1_13:
			movzx eax, word ptr[ecx + 1];
			add eax, SHIFT_4;

		issue_7_1_xx:
			add ecx, 2;

		issue_7_1_yy:
			mov word ptr[fnamew + esi], ax;
			inc ecx;
			add esi, 2;
			jmp issue_7_1_loop_start;

		issue_7_1_loop_end:
			push 0; // ?
			push 200; // dst-buf-len 
			push buff; // dst
			lea eax, fnamew; // src
			push eax;
			call PHYSFS_utf8FromUcs2;
			add esp, 0x10;

			lea ecx, dword ptr[ebp - 0x74];
			//mov dword ptr[ecx + 0x10], esi;
			//mov dword ptr[ecx + 0x14], 0x10;

			pop esi;
			pop ebx;
			pop edx;

			mov dword ptr[ebp - 0x30], 0;

			push filenameEncode_v310_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t filenameEncode_hook(RunOptions *options) {

		std::string desc = "file name encode";

		switch (options->version) {
		case v3_0_0:
		case v3_0_X:
			// push eax
			byte_pattern::temp_instance().find_pattern("50 8D 8D 78 FF FF FF C7 45 D0 00 00 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), filenameEncode_v300_start);
				// mov [ebp+var_30],0 
				filenameEncode_v300_end = byte_pattern::temp_instance().get_first().address(0x7);
			}
			else return CK2ERROR1;
			return NOERROR;
		case v3_1_0:
			// push eax
			byte_pattern::temp_instance().find_pattern("50 8D 4D 8C C7 45 D0 00 00 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), filenameEncode_v310_start);
				// mov byte ptr [ebp+var_40],0
				filenameEncode_v310_end = byte_pattern::temp_instance().get_first().address(0xB);
			}
			else return CK2ERROR1;
			return NOERROR;
		case v2_8_X:
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	inline wchar_t UCS2ToCP1252(int cp) {
		wchar_t result = cp;
		switch (cp) {
		case 0x20AC: result = 0x80; break;
		case 0x201A: result = 0x82; break;
		case 0x0192: result = 0x83; break;
		case 0x201E: result = 0x84; break;
		case 0x2026: result = 0x85; break;
		case 0x2020: result = 0x86; break;
		case 0x2021: result = 0x87; break;
		case 0x02C6: result = 0x88; break;
		case 0x2030: result = 0x89; break;
		case 0x0160: result = 0x8A; break;
		case 0x2039: result = 0x8B; break;
		case 0x0152: result = 0x8C; break;
		case 0x017D: result = 0x8E; break;
		case 0x2018: result = 0x91; break;
		case 0x2019: result = 0x92; break;
		case 0x201C: result = 0x93; break;
		case 0x201D: result = 0x94; break;
		case 0x2022: result = 0x95; break;
		case 0x2013: result = 0x96; break;
		case 0x2014: result = 0x97; break;
		case 0x02DC: result = 0x98; break;
		case 0x2122: result = 0x99; break;
		case 0x0161: result = 0x9A; break;
		case 0x203A: result = 0x9B; break;
		case 0x0153: result = 0x9C; break;
		case 0x017E: result = 0x9E; break;
		case 0x0178: result = 0x9F; break;
		}

		return result;
	}

	errno_t convertWideTextToEscapedText(const wchar_t* from, char** to) {

		errno_t success = 0;
		int toIndex = 0;
		unsigned int size = 0;

		/* */
		if (from == NULL) {
			success = 1;
			goto A;
		}

		/* */
		size = wcslen(from);

		/* 全部エスケープしても３倍を超えることはない。１０はバッファ*/
		*to = (char*)calloc(size * 3 * 2 + 10, sizeof(char));

		if (*to == NULL) {
			success = 2;
			goto A;
		}

		/* */
		toIndex = 0;
		for (unsigned int fromIndex = 0; fromIndex < size; fromIndex++) {
			wchar_t cp = from[fromIndex];

			/* */
			if (UCS2ToCP1252(cp) != cp) {
				(*to)[toIndex++] = (byte)cp;
				continue;
			}

			/* ずらす */
			if (cp > 0x100 && cp < 0xA00) {
				cp = cp + 0xE000;
			}

			/* 上位バイト */
			byte high = (cp >> 8) & 0x000000FF;

			/* 下位バイト */
			byte low = cp & 0x000000FF;

			byte escapeChr = 0x10;

			/* 2byteじゃない */
			if (high == 0) {
				(*to)[toIndex++] = (byte)cp;
				continue;
			}

			/* high byteより決定 */
			switch (high) {
			case 0xA4:case 0xA3:case 0xA7:case 0x24:case 0x5B:case 0x00:case 0x5C:
			case 0x20:case 0x0D:case 0x0A:case 0x22:case 0x7B:case 0x7D:case 0x40:
			case 0x80:case 0x7E:case 0x2F:case 0xBD:case 0x3B:case 0x5D:case 0x5F:
			case 0x3D:case 0x23:
				escapeChr += 2;
				break;
			default:
				break;
			}

			/* low byteより決定 */
			switch (low) {
			case 0xA4:case 0xA3:case 0xA7:case 0x24:case 0x5B:case 0x00:case 0x5C:
			case 0x20:case 0x0D:case 0x0A:case 0x22:case 0x7B:case 0x7D:case 0x40:
			case 0x80:case 0x7E:case 0x2F:case 0xBD:case 0x3B:case 0x5D:case 0x5F:
			case 0x3D:case 0x23:
				escapeChr++;
				break;
			default:
				break;
			}

			switch (escapeChr) {
			case 0x11:
				low += 14;
				break;
			case 0x12:
				high -= 9;
				break;
			case 0x13:
				low += 14;
				high -= 9;
				break;
			case 0x10:
			default:
				break;
			}

			(*to)[toIndex++] = escapeChr;
			(*to)[toIndex++] = low;
			(*to)[toIndex++] = high;
		}

	A:
		return success;
	}

	errno_t convertTextToWideText(const char* from, wchar_t **to) {

		errno_t success = 0;
		unsigned int err = 0;
		unsigned int wideTextSize = 0;

		/* */
		if (from == NULL) {
			success = 1;
			goto A;
		}

		/* */
		wideTextSize = MultiByteToWideChar(
			CP_UTF8,
			NULL,
			from,
			-1,
			NULL,
			NULL);

		if (wideTextSize == NULL) {
			success = GetLastError();
			goto A;
		}

		/* */
		*to = (wchar_t*)calloc(wideTextSize, sizeof(wchar_t));

		if (*to == NULL) {
			success = 3;
			goto A;
		}

		/* */
		err = MultiByteToWideChar(
			CP_UTF8,
			NULL,
			from,
			-1,
			*to,
			wideTextSize);

		if (err == NULL) {
			success = 4;
			goto B;
		}

		goto A;

	B:
		free(*to);
	A:
		return success;
	}

	/*-----------------------------------------------*/

	V* tmpZV = NULL;
	char*  utf8ToEscapedStr(char *from) {

		if (tmpZV != NULL) {
			if (tmpZV->len > 0x10) {
				free(tmpZV->t.p);
			}
			delete tmpZV;
		}

		tmpZV = new V();

		wchar_t *tmp = NULL;
		char *tmp2 = NULL;

		char *src = NULL;

		if (*(from + 0x10) >= 0x10) {
			src = (char*)(*((uintptr_t*)from));
		}
		else {
			src = from;
		}

		//UTF-8 -> wide char (ucs2)
		convertTextToWideText(src, &tmp);

		//wide char (ucs2) -> Escaped Text
		convertWideTextToEscapedText(tmp, &tmp2);

		free(tmp);

		int len = strlen(tmp2);
		tmpZV->len = len;
		tmpZV->len2 = len;

		if (len >= 0x10) {
			tmpZV->t.p = tmp2;
		}
		else {
			memcpy(tmpZV->t.text, tmp2, len);
		}

		return (char*)tmpZV;
	}

	char titleUtf8tmp[200] = {};
	char titleMytmp[200] = {};

	/*-----------------------------------------------*/

	uintptr_t issue_15_loadgame_end_v300;
	__declspec(naked) void issue_15_loadgame_start_v300() {
		__asm {
			push ecx;
			push edx;

			lea eax, [ebp-0x2C];
			push eax;
			call utf8ToEscapedStr;
			add esp, 4;

			pop edx;
			pop ecx;

			push 0;
			push eax;

			push issue_15_loadgame_end_v300;
			ret;

		}
	}

	uintptr_t issue_15_loadgame_end_v310;
	__declspec(naked) void issue_15_loadgame_start_v310() {
		__asm {
			push edx;

			mov eax, esi;
			push eax;
			call utf8ToEscapedStr;
			add esp, 4;

			pop edx;

			push dword ptr [ebp + 0xC];
			push eax;

			mov ecx, [edi + 0x90];

			push issue_15_loadgame_end_v310;
			ret;

		}
	}

	/*-----------------------------------------------*/

	errno_t loadgame_showTitle_hook(RunOptions *options) {

		std::string desc = "show title";

		switch (options->version) {
		case v3_0_0:
		case v3_0_X:
			// push 1
			byte_pattern::temp_instance().find_pattern("6A 01 40 50 FF 75 D4 EB 3A");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// lea eax, [ebp+var_2C]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(-0x2E), issue_15_loadgame_start_v300);
				// call xxxxx
				issue_15_loadgame_end_v300 = byte_pattern::temp_instance().get_first().address(-0x2E + 6);
			}
			else return CK2ERROR1;
			return NOERROR;
		case v3_1_0:
			// 関数化された？ 変更した
			// push [ebp+arg_4] 
			byte_pattern::temp_instance().find_pattern("FF 75 0C 8B 8F 90 00 00 00 56");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// lea eax, [ebp+var_2C]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), issue_15_loadgame_start_v310);
				// call xxxxx
				issue_15_loadgame_end_v310 = byte_pattern::temp_instance().get_first().address(0xA);
			}
			else return CK2ERROR1;
			return NOERROR;
		case v2_8_X:
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t fileEnumSkip_hook(RunOptions *options) {
		std::string desc = "file enum";

		switch (options->version) {
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
			byte_pattern::temp_instance().find_pattern("74 0E 78 0A 8A 41 01 41");
			if (byte_pattern::temp_instance().has_size(2, desc)) {
				// jz short loc_XXXXX -> jmp XXXXX
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(1).address(), 0xEB, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		case v2_8_X:
			return NOERROR;
		}

		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("file save etc");

		/* ファイル名を安全にしている場所を短絡する jmp [address] */
		// EU4はこれだけで大丈夫だった
		//result |= fileNameSaftySkip_hook(options); // OK

		/* ファイル名を安全にしている場所を短絡する２ jmp [address] */
		result |= fileNameSaftySkip2_hook(options); // OK

		/* ファイル名を変換する */
		result |= filenameEncode_hook(options);

		/* 変換関数を探してくる */
		result |= PHYSFS_utf8FromUcs2_hook(options); // OK

		/* タイトルを表示できるようにする */
		result |= loadgame_showTitle_hook(options);

		/* UTF-8ファイルを列挙できるようにする jz(74) -> jmp(EB) */
		result |= fileEnumSkip_hook(options); // OK

		return result;
	}
}