#pragma once
#include "stdinc.h"

namespace BitmapFont
{
    struct SBitmapCharacterValue
    {
        int16_t x;
        int16_t y;
        int16_t w;
        int16_t h;
        int16_t xoff;
        int16_t yoff;
        int16_t xadvance;
        bool kerning;
    };
    VALIDATE_SIZE(SBitmapCharacterValue, 0x10)

    typedef std::unordered_map<std::uint32_t, SBitmapCharacterValue> ValuesContainer;

    class CBitmapCharacterSet :public IncompleteClass
    {
    public:
        ValuesContainer *GetContainer();
        SBitmapCharacterValue *GetCharacterValue(std::uint32_t character);
    };

    class CBitmapFont :public IncompleteClass
    {
    public:
        CBitmapCharacterSet * GetCharacterSet();
        int GetWidthOfString(const char *text, int len, bool useSpecial);
        int GetPaddingWidth(bool useSpecial);
    };

    void InitAndPatch();
}
