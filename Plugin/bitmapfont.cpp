#include "bitmapfont.h"
#include "misc.h"
#include "eu4.h"
#include "byte_pattern.h"

namespace BitmapFont
{
    static char *pOriginalText;
    static char *pWord;
    static char *pText;

    ValuesContainer *CBitmapCharacterSet::GetContainer()
    {
        if (get_field<ValuesContainer *, 0>() == nullptr)
        {
            *field<ValuesContainer *, 0>() = new ValuesContainer;
        }

        return get_field<ValuesContainer *, 0>();
    }

    SBitmapCharacterValue *CBitmapCharacterSet::GetCharacterValue(std::uint32_t character)
    {
        auto *container = GetContainer();

        auto it = container->find(character);

        if (it != container->end())
        {
            return &it->second;
        }
        else
        {
            if (Misc::IsLatin1Char(character))
                return nullptr;
            else
                return &container->find(L'¿')->second;
        }
    }

    CBitmapCharacterSet *CBitmapFont::GetCharacterSet()
    {
        return field<CBitmapCharacterSet, 0xB4>();
    }

    int CBitmapFont::GetWidthOfString(const char *text, int len, bool useSpecial)
    {
        return injector::thiscall<int(CBitmapFont *, const char *, int, bool)>::vtbl<12>(this, text, len, useSpecial);
    }

    int CBitmapFont::GetPaddingWidth(bool useSpecial)
    {
        return injector::thiscall<int(CBitmapFont *, bool)>::vtbl<21>(this, useSpecial);
    }

    //------------------------------------------------------------------------------------------------

    //8B 04 B7 85 C0 74 0B 6A 10
    //5
    struct CBitmapCharacterSetDtorHook
    {
        void operator()(injector::reg_pack &regs) const
        {
            CBitmapCharacterSet *pSet = regs.edi;

            if (pSet->GetContainer())
            {
                delete pSet->GetContainer();
                regs.esi.i = 256;
            }

            regs.ef.zero_flag = true;
        }
    };

    //6a 10 e8 ? ? ? ? 8b 4d d0
    //5 (nop e8 call)
    //89 84 8a b4 00 00 00
    //7
    struct CBitmapFontParseFontFile_AllocValue
    {
        void operator()(injector::reg_pack &regs) const
        {
            CBitmapFont *pFont = *(CBitmapFont **)(regs.ebp.i - 0x10);
            uint32_t character = *(uint32_t *)(regs.ebp.i - 0x14);

            regs.eax.p = &pFont->GetCharacterSet()->GetContainer()->operator[](character);
        }
    };

    //8a 04 30 88 85 60 ff ff ff
    //20
    struct CBitmapFontRenderToTexture_ReadChar
    {
        void operator()(injector::reg_pack &regs) const
        {
            CString *pRight = regs.ecx;

            //初始化右值
            pRight->_length = 0;
            pRight->_capacity = 15;

            char *pSrc = (char *)regs.eax + regs.esi.i;
            char *pDst = pRight->_sso_head;

            ptrdiff_t length = eu4utf8::internal::sequence_length(pSrc);

            strncpy(pDst, pSrc, length);
            pDst[length] = 0;
            pRight->_length = length;

            regs.eax.p = pRight;
        }
    };

    //8A 04 30 0F B6 C0 8B 84 87 B4 00 00 00
    //13
    struct CBitmapFont_RenderToTexture_GetCharInfo1
    {
        void operator()(injector::reg_pack &regs) const
        {
            CBitmapFont *pFont = regs.edi;
            bool useSpecialChars = *(bool *)(regs.ebp.i + 0x3C);

            Misc::GetTwoUnicode(regs.eax, regs.esi.i, useSpecialChars);
            regs.esi.i += (Misc::context.unicodeLength - 1);

            regs.eax.p = pFont->GetCharacterSet()->GetCharacterValue(Misc::context.unicode);
        }
    };

    //66 83 78 06 00 0F 85
    //5
    struct CBitmapFontRenderToTexture_Delim
    {
        void operator()(injector::reg_pack &regs) const
        {
            SBitmapCharacterValue *pInfo = regs.eax;

            if (pInfo->h == 0 || !Misc::IsLatin1Char(Misc::context.unicode))
            {
                regs.ef.zero_flag = true;
            }
            else
            {
                regs.ef.zero_flag = false;
            }
        }
    };

    //0F B6 04 38 8B 04 81
    //7
    struct CBitmapFontRenderToTexture_GetCharInfo2
    {
        void operator()(injector::reg_pack &regs) const
        {
            CBitmapCharacterSet *pSet = regs.ecx;
            bool useSpecialChars = *(bool *)(regs.ebp.i + 0x3C);

            Misc::GetTwoUnicode(regs.eax, regs.edi.i, useSpecialChars);

            regs.edi.i += (Misc::context.unicodeLength - 1);
            *(uint32_t *)(regs.ebp.i - 0x1C) = regs.edi.i;

            regs.eax.p = pSet->GetCharacterValue(Misc::context.unicode);
        }
    };

    //8A 87 ? ? ? ? 88 86 ? ? ? ? 46
    //13
    struct CBitmapFontRenderToScreen_ReadChar
    {
        void operator()(injector::reg_pack &regs) const
        {
            CBitmapFont *pFont = *(CBitmapFont **)(regs.ebp.i - 0x10);

            bool useSpecialChars = *(bool *)(regs.ebp.i + 0x3C);

            Misc::GetTwoUnicode(pOriginalText, regs.edi.i, useSpecialChars);

            regs.eax.i = Misc::context.unicode;
            eu4utf8::append(Misc::context.unicode, pWord + regs.esi.i);
            regs.esi.i += Misc::context.unicodeLength;
            regs.edi.i += (Misc::context.unicodeLength - 1);
            *(uint32_t *)(regs.ebp.i - 0x24) = regs.edi.i;

            if (!Misc::IsLatin1Char(Misc::context.unicode))
            {
                regs.ecx.i = 0;
            }
        }
    };

    //0F B6 C0 8B 0C 82
    //6
    struct CBitmapFontRenderToScreen_GetCharInfo1
    {
        void operator()(injector::reg_pack &regs) const
        {
            CBitmapCharacterSet *pSet = *(CBitmapCharacterSet **)(regs.ebp.i - 0x3C);

            regs.eax.i = Misc::context.unicode;
            regs.ecx.p = pSet->GetCharacterValue(Misc::context.unicode);
        }
    };

    //66 83 79 06 00
    //5
    struct CBitmapFontRenderToScreen_Delim
    {
        void operator()(injector::reg_pack &regs) const
        {
            SBitmapCharacterValue *pInfo = regs.ecx;

            if (pInfo->h == 0 || !Misc::IsLatin1Char(Misc::context.unicode))
            {
                regs.ef.zero_flag = true;
            }
            else
            {
                regs.ef.zero_flag = false;
            }
        }
    };

    //8B B4 87 B4 00 00 00
    //7
    struct CBitmapFontRenderToScreen_GetCharInfo2
    {
        void operator()(injector::reg_pack &regs) const
        {
            CBitmapFont *pFont = regs.edi;
            bool useSpecialChars = *(bool *)(regs.ebp.i + 0x3C);

            Misc::GetTwoUnicode(pText, regs.edx.i, useSpecialChars);

            regs.ecx.i = Misc::context.unicode;

            regs.edx.i += (Misc::context.unicodeLength - 1);
            *(uint32_t *)(regs.ebp.i + 0x34) = regs.edx.i;

            regs.esi.p = pFont->GetCharacterSet()->GetCharacterValue(Misc::context.unicode);
        }
    };

    //0F B6 04 30 8B 0C 82
    //7
    struct CBitmapFontGetHeightOfString_GetCharInfo
    {
        void operator()(injector::reg_pack &regs) const
        {
            CBitmapCharacterSet *pSet = regs.edx;
            bool useSpecialChars = *(bool *)(regs.ebp.i + 0x18);

            Misc::GetTwoUnicode(regs.eax, regs.esi.i, useSpecialChars);

            regs.ecx.p = pSet->GetCharacterValue(Misc::context.unicode);
            regs.esi.i += (Misc::context.unicodeLength - 1);
        }
    };

    //80 3C 30 20 0F 85 CC FD FF FF
    //10
    __declspec(naked) void CBitmapFontGetHeightOfString_Delim()
    {
        __asm
        {
            pop ecx;

            cmp Misc::context.unicode, 0x20;
            jz back;

            cmp Misc::context.unicode, 0xFF;
            jg back;

            add ecx, -0x22F;

        back:
            jmp ecx;
        }
    }

    //0F B6 C2 8B 3C 81
    //6
    struct CBitmapFontGetWidthOfString_GetCharInfo
    {
        void operator()(injector::reg_pack &regs) const
        {
            CBitmapCharacterSet *pSet = regs.ecx;
            bool useSpecialChars = *(bool *)(regs.ebp.i + 0x10);

            const char *pStr = *(const char **)(regs.ebp.i + 8);

            Misc::GetTwoUnicodeSized(pStr, regs.ebx.i, regs.esi.i, useSpecialChars);

            regs.edx.i = Misc::context.unicode;
            regs.edi.p = pSet->GetCharacterValue(Misc::context.unicode);
            regs.esi.i += (Misc::context.unicodeLength - 1);
        }
    };

    //66 83 7F 06 00
    //5
    struct CBitmapFontGetWidthOfString_Delim
    {
        void operator()(injector::reg_pack &regs) const
        {
            SBitmapCharacterValue *pInfo = regs.edi;

            if (pInfo->h == 0 || !Misc::IsLatin1Char(Misc::context.unicode))
            {
                regs.ef.zero_flag = true;
            }
            else
            {
                regs.ef.zero_flag = false;
            }
        }
    };

    //----------------------------------------------------------------------------------------------
    //FillVertexBuffer

    //
    //
    struct CBitmapFontFillVertexBuffer_What
    {
        void operator()(injector::reg_pack &regs) const
        {

        }
    };

    //8A 04 38 8D 4D 80
    //17
    struct CBitmapFontFillVertexBuffer_ReadChar1
    {
        void operator()(injector::reg_pack &regs) const
        {
            CString *pRight = (CString *)(regs.ebp.i - 0x80);

            //Initialize
            pRight->_sso_head[0] = 0;
            pRight->_length = 0;
            pRight->_capacity = 15;

            Misc::GetTwoUnicode(regs.eax, regs.edi.i, false);

            eu4utf8::append(Misc::context.unicode, pRight->_sso_head);
            pRight->_sso_head[Misc::context.unicodeLength] = 0;
            pRight->_length = Misc::context.unicodeLength;

            regs.eax.p = pRight;
        }
    };

    //8B 94 81 B4 00 00 00
    //7
    struct CBitmapFontFillVertexBuffer_GetCharInfo1
    {
        void operator()(injector::reg_pack &regs) const
        {
            CBitmapFont *pFont = regs.ecx;
            regs.edx.p = pFont->GetCharacterSet()->GetCharacterValue(Misc::context.unicode);
            regs.edi.i += (Misc::context.unicodeLength - 1);
        }
    };

    //66 83 7A 06 00 0F 85 DB 01 00 00
    //5
    struct CBitmapFontFillVertexBuffer_Delim
    {
        void operator()(injector::reg_pack &regs) const
        {
            BitmapFont::SBitmapCharacterValue *pInfo = regs.edx;

            if (pInfo->h == 0 || !Misc::IsLatin1Char(Misc::context.unicode))
            {
                regs.ef.zero_flag = true;
            }
            else
            {
                regs.ef.zero_flag = false;
            }
        }
    };

    //0F B6 04 30 8B 3C 83
    //7
    struct CBitmapFontFillVertexBuffer_GetCharInfo2
    {
        void operator()(injector::reg_pack &regs) const
        {
            CBitmapCharacterSet *pSet = regs.ebx;

            Misc::GetTwoUnicode(regs.eax, regs.esi.i, false);

            regs.esi.i += (Misc::context.unicodeLength - 1);

            regs.edi.p = pSet->GetCharacterValue(Misc::context.unicode);
        }
    };
    
    //----------------------------------------------------------------------------------------------

    //8B 0C 81 8B 45 D8 89 4D D0
    //6
    struct CBitmapFontGetActualRequiredSize_GetCharInfo
    {
        void operator()(injector::reg_pack &regs) const
        {
            CString *pString = regs.esi;
            CBitmapCharacterSet *pSet = regs.ecx;

            Misc::GetTwoUnicode(pString->c_str(), regs.edi.i, true);

            regs.eax.p = pSet;
            regs.ecx.p = pSet->GetCharacterValue(Misc::context.unicode);
            regs.edi.i += (Misc::context.unicodeLength - 1);
        }
    };

    //0F BF 41 06 0F 57 C9
    //7
    __declspec(naked) void CBitmapFontGetActualRequiredSize_Delim()
    {

        __asm
        {
            movsx eax, word ptr[ecx + 6];
            xorps xmm1, xmm1;
            pop ecx;

            cmp Misc::context.unicode, 0xFF;
            jle back;
            xor eax, eax;

        back:
            jmp ecx;
        }
    };

    //8A 04 30 0F B6 C0 8B 14 82
    //9
    struct CBitmapFontGetRequiredSize_GetCharInfo
    {
        void operator()(injector::reg_pack &regs) const
        {
            CBitmapCharacterSet *pSet = regs.edx;
            bool useSpecialChars = *(bool *)(regs.ebp.i + 0x1C);

            Misc::GetTwoUnicode(regs.eax, regs.esi.i, useSpecialChars);

            regs.edx.p = pSet->GetCharacterValue(Misc::context.unicode);
            regs.esi.i += (Misc::context.unicodeLength - 1);
        }
    };

    //8A 04 30 3C 20
    //5
    struct CBitmapFontGetActualRequiredSizeActually_IsSpace
    {
        void operator()(injector::reg_pack &regs) const
        {
            bool useSpecialChars = *(bool *)(regs.ebp.i + 0x24);
            Misc::GetTwoUnicode(regs.eax, regs.esi.i, useSpecialChars);

            if (Misc::context.unicode == 0x20 || !Misc::IsLatin1Char(Misc::context.unicode))
            {
                regs.ef.zero_flag = true;
            }
            else
            {
                regs.ef.zero_flag = false;
            }
        }
    };

    //8A 04 30 8B 55 14 0F B6 C0 8B 14 82
    //12
    struct CBitmapFontGetActualRequiredSizeActually_GetCharInfo
    {
        void operator()(injector::reg_pack &regs) const
        {
            bool useSpecialChars = *(bool *)(regs.ebp.i + 0x24);
            CBitmapCharacterSet *pSet = *(CBitmapCharacterSet **)(regs.ebp.i + 0x14);

            Misc::GetTwoUnicode(regs.eax, regs.esi.i, useSpecialChars);
            regs.esi.i += (Misc::context.unicodeLength - 1);
            regs.edx.p = pSet->GetCharacterValue(Misc::context.unicode);
        }
    };

    void InitAndPatch()
    {
        //~BitmapCharacterSet
        byte_pattern::temp_instance().find_pattern("8B 04 B7 85 C0 74 0B 6A 10");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapCharacterSetDtorHook>(byte_pattern::temp_instance().get_first().address());

        //ParseFontFile
        byte_pattern::temp_instance().find_pattern("6a 10 e8 ? ? ? ? 8b 4d d0");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontParseFontFile_AllocValue>(byte_pattern::temp_instance().get_first().address(2));

        byte_pattern::temp_instance().find_pattern("89 84 8a b4 00 00 00");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeNOP(byte_pattern::temp_instance().get_first().address(), 7);

        //RenderToTexture
        byte_pattern::temp_instance().find_pattern("8a 04 30 88 85 60 ff ff ff");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontRenderToTexture_ReadChar>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(20));

        byte_pattern::temp_instance().find_pattern("8A 04 30 0F B6 C0 8B 84 87 B4 00 00 00");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFont_RenderToTexture_GetCharInfo1>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(13));

        byte_pattern::temp_instance().find_pattern("66 83 78 06 00 0F 85");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontRenderToTexture_Delim>(byte_pattern::temp_instance().get_first().address());

        byte_pattern::temp_instance().find_pattern("0F B6 04 38 8B 04 81");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontRenderToTexture_GetCharInfo2>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(7));

        //RenderToScreen
        byte_pattern::temp_instance().find_pattern("68 00 0C 00 00 50 68");
        if (byte_pattern::temp_instance().has_size(1))
            pOriginalText = *byte_pattern::temp_instance().get_first().pointer<char *>(7);

        byte_pattern::temp_instance().find_pattern("68 3C 0C 00 00 6A 00 68");
        if (byte_pattern::temp_instance().has_size(1))
            pText = *byte_pattern::temp_instance().get_first().pointer<char *>(8);

        byte_pattern::temp_instance().find_pattern("68 00 01 00 00 6A 00 68");
        if (byte_pattern::temp_instance().has_size(1))
            pWord = *byte_pattern::temp_instance().get_first().pointer<char *>(8);

        byte_pattern::temp_instance().find_pattern("8A 87 ? ? ? ? 88 86 ? ? ? ? 46");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontRenderToScreen_ReadChar>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(13));

        byte_pattern::temp_instance().find_pattern("0F B6 C0 8B 0C 82");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontRenderToScreen_GetCharInfo1>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(6));

        byte_pattern::temp_instance().find_pattern("66 83 79 06 00");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontRenderToScreen_Delim>(byte_pattern::temp_instance().get_first().address());

        byte_pattern::temp_instance().find_pattern("8B B4 87 B4 00 00 00");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontRenderToScreen_GetCharInfo2>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(7));

       //GetHeightOfString
        byte_pattern::temp_instance().find_pattern("0F B6 04 30 8B 0C 82");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontGetHeightOfString_GetCharInfo>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(7));

        byte_pattern::temp_instance().find_pattern("80 3C 30 20 0F 85 CC FD FF FF");
        if (byte_pattern::temp_instance().has_size(1))
        {
            injector::MakeNOP(byte_pattern::temp_instance().get_first().address(), 10);
            injector::MakeCALL(byte_pattern::temp_instance().get_first().address(), CBitmapFontGetHeightOfString_Delim);
        }
        //GetWidthOfString
        byte_pattern::temp_instance().find_pattern("0F B6 C2 8B 3C 81");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontGetWidthOfString_GetCharInfo>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(6));

        byte_pattern::temp_instance().find_pattern("66 83 7F 06 00");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontGetWidthOfString_Delim>(byte_pattern::temp_instance().get_first().address());

        //FillVertexBuffer
        byte_pattern::temp_instance().find_pattern("8A 04 38 8D 4D 80");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontFillVertexBuffer_ReadChar1>(byte_pattern::temp_instance().get_first().pointer(), byte_pattern::temp_instance().get_first().pointer(17));

        byte_pattern::temp_instance().find_pattern("8B 94 81 B4 00 00 00");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontFillVertexBuffer_GetCharInfo1>(byte_pattern::temp_instance().get_first().pointer(), byte_pattern::temp_instance().get_first().pointer(7));

        byte_pattern::temp_instance().find_pattern("66 83 7A 06 00 0F 85 DB 01 00 00");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontFillVertexBuffer_Delim>(byte_pattern::temp_instance().get_first().pointer());

        byte_pattern::temp_instance().find_pattern("0F B6 04 30 8B 3C 83");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontFillVertexBuffer_GetCharInfo2>(byte_pattern::temp_instance().get_first().pointer(), byte_pattern::temp_instance().get_first().pointer(7));

        //GetActualRequiredSize
        byte_pattern::temp_instance().find_pattern("8B 0C 81 8B 45 D8 89 4D D0");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontGetActualRequiredSize_GetCharInfo>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(6));

        byte_pattern::temp_instance().find_pattern("0F BF 41 06 0F 57 C9");
        if (byte_pattern::temp_instance().has_size(1))
        {
            injector::MakeNOP(byte_pattern::temp_instance().get_first().address(), 7);
            injector::MakeCALL(byte_pattern::temp_instance().get_first().address(), CBitmapFontGetActualRequiredSize_Delim);
        }

        //GetRequiredSize
        byte_pattern::temp_instance().find_pattern("8A 04 30 0F B6 C0 8B 14 82");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontGetRequiredSize_GetCharInfo>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(9));

        //GetActualRealRequiredSizeActually
        byte_pattern::temp_instance().find_pattern("8A 04 30 3C 20");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontGetActualRequiredSizeActually_IsSpace>(byte_pattern::temp_instance().get_first().address());

        byte_pattern::temp_instance().find_pattern("8A 04 30 8B 55 14 0F B6 C0 8B 14 82");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CBitmapFontGetActualRequiredSizeActually_GetCharInfo>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(12));
    }
}
