#pragma once
#include "stdinc.h"
#include "eu4.h"
#include "bitmapfont.h"

namespace TextBuffer
{
    class CTextBuffer :IncompleteClass
    {
        //0x1C: CString: string
        //0x1C: CCursorPosition: position
        //0x48: unsigned short: line width
        //0x70: void *: pFont
        //0xAC: bool: use special char
        //0xB0: CArray<CRow>: rows
    public:
        CString *GetString();
        BitmapFont::CBitmapFont *GetFont();
        bool GetUseSpecialChar();
        unsigned short GetLineWidth();

        static int __fastcall GetLineCharSize(CTextBuffer *pBuffer, int edx, const CString *szText);
    };

    void InitAndPatch();
}
