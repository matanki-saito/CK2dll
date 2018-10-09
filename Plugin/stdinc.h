#pragma once

#define NOMINMAX

#include <windows.h>
#include <cstdint>
#include <cstddef>
#include <fstream>
#include <utility>
#include <unordered_map>
#include <string>
#include <iterator>
#include <algorithm>
#include <utility>
#include <cstring>
#include <filesystem>
#include <boost/utility/string_view.hpp>
#include "../include/injector/hooking.hpp"
#include "../include/injector/calling.hpp"
#include "../include/injector/assembly.hpp"

#define VALIDATE_SIZE(type,size) static_assert(sizeof(type)==size, "Type size error.");

struct IncompleteClass
{
    template <typename T, std::uintptr_t offset>
    T *field()
    {
        return (T *)(reinterpret_cast<std::uintptr_t>(this) + offset);
    }

    template <typename T, std::uintptr_t offset>
    T get_field()
    {
        return *(T *)(reinterpret_cast<std::uintptr_t>(this) + offset);
    }
};

#define ESCAPE_SEQ_1 0x10
#define ESCAPE_SEQ_2 0x11
#define ESCAPE_SEQ_3 0x12
#define ESCAPE_SEQ_4 0x13

#define LOW_SHIFT 0x0F
#define HIGH_SHIFT 0x9

#define SHIFT_2 LOW_SHIFT
#define SHIFT_3 0x900
#define SHIFT_4 0x8F1

#define NO_FONT 0x98F
#define NOT_DEF 0x2026

#define CK2ERROR1 0x10000

enum CK2Version {
	UNKNOWN = 0,
	v2_7_X = 27,
	v2_8_X = 28,
	v2_9_X = 29
};

namespace Misc
{
	CK2Version getVersion();
	std::string versionString(CK2Version version);
	errno_t init(CK2Version version);
}

namespace MapView
{
	errno_t init(CK2Version version);
}

namespace MapJustify
{
	errno_t init(CK2Version version);
}

namespace Font
{
	errno_t init(CK2Version version);
}

namespace DecorativeLetterEndDialog
{
	errno_t init(CK2Version version);
}

namespace DecorativeLetterDialog
{
	errno_t init(CK2Version version);
}

namespace DecorativeLetterInheritDialog
{
	errno_t init(CK2Version version);
}

namespace ButtonAndTooltip
{
	errno_t init(CK2Version version);
}

namespace MainText
{
	errno_t init(CK2Version version);
}

namespace NickNameFix
{
	errno_t init(CK2Version version);
}

namespace NoDynastyId
{
	errno_t init(CK2Version version);
}

namespace IME
{
	errno_t init(CK2Version version);
}

namespace Input
{
	errno_t init(CK2Version version);
}

namespace MapAdj
{
	errno_t init(CK2Version version);
}

namespace Unk1
{
	errno_t init(CK2Version version);
}

namespace Unk2
{
	errno_t init(CK2Version version);
}