#include "util.hpp"
#include <iostream>

namespace Util
{
    bool pointInRect(float x, float y, SDL_FRect rect)
    {
        return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
    }
}