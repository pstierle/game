#include "global.hpp"

extern State state;

namespace Util
{
    bool intersects(SDL_FRect rect1, SDL_FRect rect2)
    {
        return (rect1.x >= rect2.x &&
                rect1.y >= rect2.y &&
                (rect1.x + rect1.w) <= (rect2.x + rect2.w) &&
                (rect1.y + rect1.h) <= (rect2.y + rect2.h));
    }

    bool pointInRect(SDL_FPoint point, SDL_FRect rect)
    {
        return point.x >= rect.x && point.x < rect.x + rect.w &&
               point.y >= rect.y && point.y < rect.y + rect.h;
    }

    int randomInRange(int from, int to)
    {
        if (from > to)
        {
            std::swap(from, to);
        }

        static std::random_device rd;
        static std::mt19937 rng(rd());

        std::uniform_int_distribution<int> distribution(from, to);

        return distribution(rng);
    }

    Particle bombExplosionParticle(SDL_FPoint position)
    {
        SDL_FPoint randomPosition = {static_cast<float>(randomInRange(position.x - 50, position.x + 50)), static_cast<float>(randomInRange(position.y - 50, position.y + 50))};
        return Particle(randomPosition, randomInRange(2, 5), randomInRange(2, 5), randomInRange(200, 1000), randomInRange(160, 255), randomInRange(0, 50), 0, 255);
    }

    Particle rockDestroyParticle(SDL_FPoint position)
    {
        int randomGrey = randomInRange(0, 180);
        SDL_FPoint randomPosition = {static_cast<float>(randomInRange(position.x - 20, position.x + 20)), static_cast<float>(randomInRange(position.y - 20, position.y + 20))};
        return Particle(randomPosition, randomInRange(2, 5), randomInRange(2, 5), randomInRange(200, 500), randomGrey, randomGrey, randomGrey, 255);
    }

    void drawRectangle(SDL_FPoint position, int width, int height)
    {
        SDL_SetRenderDrawColor(state.renderer, 255, 0, 0, 255);
        SDL_FRect rect = {position.x, position.y, static_cast<float>(width), static_cast<float>(height)};
        SDL_RenderDrawRectF(state.renderer, &rect);
    }
}