#include "province.h"
#include "misc.h"
#include "eu4.h"
#include "bitmapfont.h"
#include "byte_pattern.h"

namespace Province
{
    using namespace std;

    //E8 ? ? ? ? 8B 45 AC 8D 55 BC
    //5
    //"ABC" --> "A B C"
    struct CGenerateNamesWorkAddNameArea_InsertSpace
    {
        void operator()(injector::reg_pack &regs) const
        {
            static vector<uint32_t> wbuffer;
            static string cbuffer;

            wbuffer.clear();
            cbuffer.clear();

            regs.esp.i += 8;
            const CString *pSource = (CString *)(regs.ebp.i - 0xC0);
            CString *pDest = regs.ecx;

            boost::string_view view(pSource->c_str());

            auto it = view.begin();

            while (it != view.end())
            {
                wbuffer.push_back(eu4utf8::next(it, view.end()));
                wbuffer.push_back(' ');
            }
            wbuffer.pop_back();

            eu4utf8::utf32to8(wbuffer.begin(), wbuffer.end(), back_inserter(cbuffer));

            Misc::assign_string(pDest, cbuffer.c_str());
        }
    };

    //0F B6 04 08 8B 04 82
    //7
    struct CGenerateNamesWorkAddNameArea_CountDrawables
    {
        void operator()(injector::reg_pack &regs) const
        {
            BitmapFont::CBitmapCharacterSet *pSet = regs.edx;

            Misc::GetTwoUnicode(regs.eax, regs.ecx.i, false);

            regs.eax.p = pSet->GetCharacterValue(Misc::context.unicode);
            regs.ecx.i += (Misc::context.unicodeLength - 1);
        }
    };

    //8B 79 10 83 FF 02
    //6
    struct CurveText_CalcExtraWidth
    {
        void operator()(injector::reg_pack &regs) const
        {
            const CString *pString = regs.ecx;

            boost::string_view view(pString->c_str());

            regs.edi.i = eu4utf8::distance(view.begin(), view.end());

            regs.ef.zero_flag = (regs.edi.i == 2);
        }
    };

    //8B 04 82 89 45 9C 85 C0
    //6
    struct CurveText_GetCharInfo
    {
        void operator()(injector::reg_pack &regs) const
        {
            BitmapFont::CBitmapCharacterSet *pSet = regs.edx;
            uint32_t index = *(uint32_t *)(regs.ebp.i - 0x1C);

            Misc::GetTwoUnicode(regs.ecx, index, false);

            *(uint32_t *)(regs.ebp.i - 0x1C) += (Misc::context.unicodeLength - 1);

            regs.eax.p = pSet->GetCharacterValue(Misc::context.unicode);
            *(void **)(regs.ebp.i - 0x64) = regs.eax.p;
        }
    };

    //3C 27 74 0D 3C 2E
    //6
    struct CurveText_CheckDots
    {
        void operator()(injector::reg_pack &regs) const
        {
            regs.ef.zero_flag = (Misc::context.unicode == 0x27 || Misc::context.unicode == 0x2E);
        }
    };

    //0F B6 04 08 8B 84 86 B4 00 00 00
    //11
    struct CCountryNameCollectionAddNudgedNames_CountDrawables
    {
        void operator()(injector::reg_pack &regs) const
        {
            BitmapFont::CBitmapFont *pFont = regs.esi;

            Misc::GetTwoUnicode(regs.eax, regs.ecx.i, false);

            regs.eax.p = pFont->GetCharacterSet()->GetCharacterValue(Misc::context.unicode);
            regs.ecx.i += (Misc::context.unicodeLength - 1);
        }
    };

    void InitAndPatch()
    {
        //AddNameArea
        byte_pattern::temp_instance().find_pattern("E8 ? ? ? ? 8B 45 AC 8D 55 BC");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CGenerateNamesWorkAddNameArea_InsertSpace>(byte_pattern::temp_instance().get_first().address());

        byte_pattern::temp_instance().find_pattern("0F B6 04 08 8B 04 82");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CGenerateNamesWorkAddNameArea_CountDrawables>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(7));
        
        //CurveText
        byte_pattern::temp_instance().find_pattern("8B 79 10 83 FF 02");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CurveText_CalcExtraWidth>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(6));

        byte_pattern::temp_instance().find_pattern("8B 04 82 89 45 9C 85 C0");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CurveText_GetCharInfo>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(6));
    
        byte_pattern::temp_instance().find_pattern("3C 27 74 0D 3C 2E");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CurveText_CheckDots>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(6));

        //AddNudgedNames
        byte_pattern::temp_instance().find_pattern("0F B6 04 08 8B 84 86 B4 00 00 00");
        if (byte_pattern::temp_instance().has_size(1))
            injector::MakeInline<CCountryNameCollectionAddNudgedNames_CountDrawables>(byte_pattern::temp_instance().get_first().address(), byte_pattern::temp_instance().get_first().address(11));
    }
}
