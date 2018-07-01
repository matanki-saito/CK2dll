#pragma once
#include "stdinc.h"

struct CCursorPosition
{
    uint16_t row;
    uint16_t column;
};

struct CInputEvent
{
    char _data[0x58];

    void Init(const char *str)
    {
        std::memset(this, 0, sizeof(CInputEvent));

        strcpy(&_data[0xC], str);
        _data[0x38] = 3;
        _data[0x50] = 2;
    }

    void Init(char character)
    {
        std::memset(this, 0, sizeof(CInputEvent));

        _data[0xC] = character;
        _data[0x38] = 3;
        _data[0x50] = 2;
    }
};
VALIDATE_SIZE(CInputEvent, 0x58)

class CString
{
public:
    union
    {
        char *_heap;
        char _sso_head[4];
    };
    char _sso_rest[12];
    std::size_t _length;
    std::size_t _capacity;

    size_t length() const
    {
        return _length;
    }

    const char *c_str() const
    {
        return _capacity > 15 ? _heap : _sso_head;
    }
};
VALIDATE_SIZE(CString, 0x18)
