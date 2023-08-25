#include "util.hpp"
#include <iostream>
#include <cmath>

namespace Util
{
    bool pointInRect(float x, float y, SDL_FRect rect)
    {
        return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
    }

    double distancePoints(SDL_FPoint point1, SDL_FPoint point2)
    {
        double dx = point2.x - point1.x;
        double dy = point2.y - point1.y;
        return std::sqrt(dx * dx + dy * dy);
    }

}