#pragma once

#include "global.hpp"

namespace Util
{
    bool pointInRect(SDL_FPoint point, SDL_FRect rect);
    int randomInRange(int from, int to);
    Particle bombExplosionParticle(SDL_FPoint position);
    Particle rockDestroyParticle(SDL_FPoint position);
    void drawRectangle(SDL_FRect positionRect, SDL_Color backgroundColor, SDL_Color borderColor, float borderWidth);
    void drawTriangle(SDL_FPoint position, int width, SDL_Color color, float angle);
    float calculateDistance(SDL_FPoint point1, SDL_FPoint point2);
}