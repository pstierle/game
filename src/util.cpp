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

    void drawRectangle(SDL_FRect positionRect, SDL_Color backgroundColor, SDL_Color borderColor, float borderWidth)
    {
        // Set the background color
        SDL_SetRenderDrawColor(state.renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
        SDL_RenderFillRectF(state.renderer, &positionRect);

        // Set the border color
        SDL_SetRenderDrawColor(state.renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);

        // Draw the border
        SDL_FRect borderRect = {
            positionRect.x - borderWidth / 2,
            positionRect.y - borderWidth / 2,
            positionRect.w + borderWidth,
            positionRect.h + borderWidth};

        SDL_RenderDrawRectF(state.renderer, &borderRect);
    }

    float calculateDistance(SDL_FPoint point1, SDL_FPoint point2)
    {
        float deltaX = point2.x - point1.x;
        float deltaY = point2.y - point1.y;

        return std::sqrt(deltaX * deltaX + deltaY * deltaY);
    }

    void drawTriangle(SDL_FPoint position, int width, SDL_Color color, float angle)
    {
        SDL_FPoint points[3];
        points[0] = {position.x, position.y};
        points[1] = {position.x + static_cast<float>(width), position.y};
        points[2] = {position.x + static_cast<float>(width) / 2, position.y + static_cast<float>(width) * 0.866f};

        SDL_SetRenderDrawColor(state.renderer, color.r, color.g, color.b, color.a);

        float centerX = (points[0].x + points[1].x + points[2].x) / 3.0f;
        float centerY = (points[0].y + points[1].y + points[2].y) / 3.0f;

        for (int i = 0; i < 3; ++i)
        {
            points[i].x -= centerX;
            points[i].y -= centerY;

            float x = points[i].x;
            points[i].x = x * std::cos(angle) - points[i].y * std::sin(angle) + centerX;
            points[i].y = x * std::sin(angle) + points[i].y * std::cos(angle) + centerY;
        }

        SDL_RenderDrawLineF(state.renderer, points[0].x, points[0].y, points[1].x, points[1].y);
        SDL_RenderDrawLineF(state.renderer, points[1].x, points[1].y, points[2].x, points[2].y);
        SDL_RenderDrawLineF(state.renderer, points[2].x, points[2].y, points[0].x, points[0].y);
    }
}