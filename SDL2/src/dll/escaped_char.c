#include "./escated_char.h"

inline UINT32 UCS2ToCP1252(UINT32 cp) {
	UINT32 result = cp;
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


BOOL WIN_ConvertUTF32toEscapedChar(UINT32 codepoint, char* text) {

	int index = 0;
	BYTE escapeChr = 0x10;

	// BMPの範囲内
	if (codepoint > 0xFFFF) {
		return SDL_FALSE;
	}

	/* CP1252の特殊な文字 */
	codepoint = UCS2ToCP1252(codepoint);

	/* ずらす */
	if (codepoint > 0x100 && codepoint < 0xA00) {
		codepoint = codepoint + 0xE000;
	}

	/* 上位バイト */
	BYTE high = (codepoint >> 8) & 0x000000FF;

	/* 下位バイト */
	BYTE low = codepoint & 0x000000FF;

	
	/* 2byteじゃない */
	if (high == 0) {
		text[index] = (BYTE)codepoint;
		return SDL_TRUE;
	}

	/* high byteより決定 */
	switch (high) {
	case 0xA4:case 0xA3:case 0xA7:case 0x24:case 0x5B:case 0x00:case 0x5C:
	case 0x20:case 0x0D:case 0x0A:case 0x22:case 0x7B:case 0x7D:case 0x40:
	case 0x80:case 0x7E:case 0x2F:case 0xBD:case 0x3B:case 0x5D:case 0x5F:
	case 0x3D:case 0x23:case 0x8:
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
	case 0x3D:case 0x23:case 0x8:
		escapeChr++;
		break;
	default:
		break;
	}

	switch (escapeChr) {
	case 0x11:
		low += 15;
		break;
	case 0x12:
		high -= 9;
		break;
	case 0x13:
		low += 15;
		high -= 9;
		break;
	case 0x10:
	default:
		break;
	}

	text[index++] = escapeChr;
	text[index++] = low;
	text[index++] = high;

	return SDL_TRUE;
}