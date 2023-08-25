#pragma once

#include <SDL2/SDL.h>

namespace Util
{
    bool pointInRect(float x, float y, SDL_FRect rect);
    double distancePoints(SDL_FPoint point1, SDL_FPoint point2);
}