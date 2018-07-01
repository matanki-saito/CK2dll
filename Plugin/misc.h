#pragma once
#include "eu4.h"

namespace Misc
{
    struct HookContext
    {
        std::uint32_t unicode;
        std::ptrdiff_t unicodeLength;
        std::uint32_t nextUnicode;
    };

    extern HookContext context;

    void __fastcall ConvertUTF8ToLatin1(const char *source, char *dest);
    bool IsLatin1Char(std::uint32_t cp);
    void GetTwoUnicode(const char * pText, std::uint32_t index, bool useSpecial);
    void GetTwoUnicodeSized(const char * pText, uint32_t length, std::uint32_t index, bool useSpecial);

    void InitAndPatch();

    void assign_string(CString *str, const char *text);
}
