#pragma once

#include "../core/windows/SDL_windows.h"
#include "SDL_stdinc.h"

BOOL WIN_ConvertUTF32toEscapedChar(UINT32 codepoint, char* text);