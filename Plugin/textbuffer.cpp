#include "textbuffer.h"
#include "misc.h"
#include "byte_pattern.h"

namespace TextBuffer
{
    CString * CTextBuffer::GetString()
    {
        return field<CString, 0x1C>();
    }

    BitmapFont::CBitmapFont * CTextBuffer::GetFont()
    {
        return get_field<BitmapFont::CBitmapFont *, 0x70>();
    }

    bool CTextBuffer::GetUseSpecialChar()
    {
        return get_field<bool, 0xAC>();
    }

    unsigned short CTextBuffer::GetLineWidth()
    {
        return get_field<unsigned short, 0x48>();
    }

    int __fastcall CTextBuffer::GetLineCharSize(CTextBuffer *pBuffer, int edx, const CString *szText)
    {
        int result = 0;
        int width = 0;
        int maxWidth = pBuffer->GetLineWidth() - pBuffer->GetFont()->GetPaddingWidth(true);

        boost::string_view view{ szText->c_str() };
        auto it = view.begin();
        auto endit = view.end();

        while (it != endit)
        {
            auto len = eu4utf8::internal::sequence_length(it);

            width += pBuffer->GetFont()->GetWidthOfString(&*it, len, pBuffer->GetUseSpecialChar());

            if (width > maxWidth)
                return result;
            else
            {
                eu4utf8::next(it, endit);
                result += len;
            }
        }

        return result;
    }

    //
    //
    struct CTextBufferWrite_RemoveSpecials
    {
        void operator()(injector::reg_pack &regs) const
        {

        }
    };

    //
    //
    struct CTextBuffer_
    {
        void operator()(injector::reg_pack &regs) const
        {

        }
    };

    struct CSdlEvents_HandlePdxEvents_ReadInputs
    {
        void operator()(injector::reg_pack &regs) const
        {
            CInputEvent temp;
            char *pText = (char *)(regs.ebp.i - 0x48);

            temp.Init(pText);
            injector::thiscall<void(void *, const CInputEvent *)>::vtbl<3>(regs.ebx, &temp);

            memset(pText, 0, 32);

            regs.ecx.i = 0;
            regs.eax.i = 0;
        }
    };

    CString *__fastcall sub_112CEE0(const char *cstr, int edx, CString *result)
    {
        //初始化
        result->_sso_head[0] = 0;
        result->_length = 0;
        result->_capacity = 15;

        Misc::assign_string(result, cstr);
        return result;
    }

    void InitAndPatch()
    {    
        //从输入接受整个字符串
        //mov ecx, [ebp - 0x48]; xor al, al
        byte_pattern::temp_instance().find_pattern("8B 4D B8 32 C0 88 45 0B");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CSdlEvents_HandlePdxEvents_ReadInputs>(byte_pattern::temp_instance().get_first().address());

        //构造整个字符串
        byte_pattern::temp_instance().find_pattern("75 C6 8D 45 DC 8B CF 50 E8");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeCALL(byte_pattern::temp_instance().get_first().address(8), sub_112CEE0);

        byte_pattern::temp_instance().find_pattern("6A 01 8B 4F 70 8B 01");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeJMP(byte_pattern::temp_instance().get_first().address(-0xB), CTextBuffer::GetLineCharSize);
    }
}
