#pragma once

#include <SDL2/SDL.h>

namespace Util
{
    bool pointInRect(int x, int y, SDL_FRect rect);
}