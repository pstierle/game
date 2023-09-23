#pragma once

#include "global.hpp"

namespace Util
{
    bool intersects(SDL_FRect rect1, SDL_FRect rect2);
    bool pointInRect(SDL_FPoint point, SDL_FRect rect);
    int randomInRange(int from, int to);
    Particle bombExplosionParticle(SDL_FPoint position);
    Particle rockDestroyParticle(SDL_FPoint position);
    void drawRectangle(SDL_FPoint position, int width, int height);
}