#pragma once

#include "global.hpp"

namespace Util
{
    bool pointInRect(SDL_FPoint point, SDL_FRect rect);
    int randomInRange(int from, int to);
    Particle bombExplosionParticle(SDL_FPoint position);
    Particle rockDestroyParticle(SDL_FPoint position);
    void createWaterParticles(SDL_FPoint position);
    void drawRectangle(SDL_FRect positionRect, SDL_Color backgroundColor, SDL_Color borderColor, float borderWidth);
    void drawTriangle(SDL_FPoint position, int width, SDL_Color color, float angle);
    float calculateDistance(SDL_FPoint point1, SDL_FPoint point2);
    bool lineIntersectsRect(SDL_FPoint lineStart, SDL_FPoint lineEnd, SDL_FRect rect);
    bool doLinesIntersect(SDL_FPoint lineStart1, SDL_FPoint lineEnd1, SDL_FPoint lineStart2, SDL_FPoint lineEnd2);
    void drawLine(SDL_FPoint start, SDL_Color color, float angle, int length);
    SDL_FPoint endpointFromLine(SDL_FPoint start, float angle, int length);
    bool pointOutOfWindow(SDL_FPoint point);
    bool rectOutOfWindow(SDL_FRect rect);
}