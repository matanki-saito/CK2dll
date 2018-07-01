#include "misc.h"
#include "eu4.h"
#include "byte_pattern.h"

using namespace std;

namespace Misc
{
    HookContext context;

    void assign_string(CString *str, const char *text)
    {
        static void *pfAssign = nullptr;

        if (pfAssign == nullptr)
        {
            byte_pattern::temp_instance().find_pattern("8B 5D 08 56 8B F1 85 DB 74 57");
            if (byte_pattern::temp_instance().has_size(2))
                pfAssign = byte_pattern::temp_instance().get(1).pointer(-4);
        }

        injector::thiscall<void(CString *, const char *, size_t)>::call(pfAssign, str, text, strlen(text));
    }

    void __fastcall ConvertUTF8ToLatin1(const char *source, char *dest)
    {
        vector<uint32_t> wideText;
        utf8::utf8to32(source, source + strlen(source), back_inserter(wideText));

        for (uint32_t &cp : wideText)
        {
            switch (cp)
            {
            case 0x80:
            case 0x82:
            case 0x83:
            case 0x84:
            case 0x85:
            case 0x86:
            case 0x87:
            case 0x88:
            case 0x89:
            case 0x8a:
            case 0x8b:
            case 0x8c:
            case 0x8e:
            case 0x91:
            case 0x92:
            case 0x93:
            case 0x94:
            case 0x95:
            case 0x96:
            case 0x97:
            case 0x98:
            case 0x99:
            case 0x9a:
            case 0x9b:
            case 0x9c:
            case 0x9e:
            case 0x9f:
                cp = '?';
                break;

            default:
                break;
            }
        }

        wideText.push_back(0);
        eu4utf8::utf32to8(wideText.begin(), wideText.end(), dest);
    }

    bool IsLatin1Char(uint32_t cp)
    {
        return cp <= 0xFF;
    }

    void GetTwoUnicode(const char *pText, uint32_t index, bool useSpecial)
    {
        size_t length = strlen(pText);

        GetTwoUnicodeSized(pText, length, index, useSpecial);
    }

    void GetTwoUnicodeSized(const char * pText, uint32_t length, std::uint32_t index, bool useSpecial)
    {
        context.nextUnicode = 0;

        try
        {
            //First
            if (index < length)
            {
                context.unicodeLength = eu4utf8::internal::sequence_length(pText + index);
                context.unicode = eu4utf8::peek_next(pText + index, pText + length);
                index += context.unicodeLength;
            }

            //Second
            if (index < length)
            {
                ptrdiff_t second_length = eu4utf8::internal::sequence_length(pText + index);
                uint32_t temp_second = eu4utf8::peek_next(pText + index, pText + length);

                if (useSpecial)
                {
                    while (temp_second == 0xA7)
                    {
                        index += 2;

                        if (index >= length)
                        {
                            return;
                        }

                        temp_second = eu4utf8::peek_next(pText + index, pText + length);
                    }
                }

                context.nextUnicode = temp_second;
            }
        }
        catch (std::exception &ex)
        {
            throw;
        }
    }

    void InitAndPatch()
    {
        //yml转码函数
        byte_pattern::temp_instance().find_pattern("81 EC B0 00 00 00 53 56 57 8B F9 8B DA");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeJMP(byte_pattern::temp_instance().get_first().address(-0x18), ConvertUTF8ToLatin1);


        //校验总是成功,不要依赖垃圾值
        byte_pattern::temp_instance().find_pattern("0F 94 45 F3 56");
        if (byte_pattern::temp_instance().has_size(1))
            //mov byte ptr[ebp-0xD], 1
            injector::WriteMemory<uint32_t>(byte_pattern::temp_instance().get_first().address(), 0x01F345C6u, true);

        //校验总是成功,不要依赖垃圾值
        byte_pattern::temp_instance().find_pattern("0F 94 45 E7 85 DB");
        if (byte_pattern::temp_instance().has_size(1))
            //mov byte ptr[ebp-0x19], 1
            injector::WriteMemory<uint32_t>(byte_pattern::temp_instance().get_first().address(), 0x01E745C6u, true);

        //贴图大小限制
        byte_pattern::temp_instance().find_pattern("81 FE 00 00 00 01");
        if (byte_pattern::temp_instance().has_size(1))
            injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(6), 0xEB, true);

        //A3 A4 A7 -> 03 04 07
        //比较 赋值 替换 格式化字符串参数
    }
}
