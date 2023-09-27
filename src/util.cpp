#include "global.hpp"

extern State state;

namespace Util
{
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
        SDL_SetRenderDrawColor(state.renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
        SDL_FRect borderRect = {
            positionRect.x - borderWidth,
            positionRect.y - borderWidth,
            positionRect.w + borderWidth * 2,
            positionRect.h + borderWidth * 2};

        SDL_RenderFillRectF(state.renderer, &borderRect);

        SDL_SetRenderDrawColor(state.renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
        SDL_RenderFillRectF(state.renderer, &positionRect);
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

    bool doLinesIntersect(SDL_FPoint lineStart1, SDL_FPoint lineEnd1, SDL_FPoint lineStart2, SDL_FPoint lineEnd2)
    {
        float x1 = lineStart1.x;
        float y1 = lineStart1.y;
        float x2 = lineEnd1.x;
        float y2 = lineEnd1.y;

        float x3 = lineStart2.x;
        float y3 = lineStart2.y;
        float x4 = lineEnd2.x;
        float y4 = lineEnd2.y;

        float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

        if (den == 0)
        {
            return false;
        }

        float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
        float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

        if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
        {
            return true;
        }

        return false;
    }

    bool lineIntersectsRect(SDL_FPoint lineStart, SDL_FPoint lineEnd, SDL_FRect rect)
    {
        if (pointInRect(lineStart, rect) || pointInRect(lineEnd, rect))
        {
            return true;
        }

        SDL_FPoint rectPoints[4];
        rectPoints[0] = {rect.x, rect.y};
        rectPoints[1] = {rect.x + rect.w, rect.y};
        rectPoints[2] = {rect.x + rect.w, rect.y + rect.h};
        rectPoints[3] = {rect.x, rect.y + rect.h};

        for (int i = 0; i < 4; ++i)
        {
            int j = (i + 1) % 4;

            SDL_FPoint edgeStart = rectPoints[i];
            SDL_FPoint edgeEnd = rectPoints[j];

            if (doLinesIntersect(lineStart, lineEnd, edgeStart, edgeEnd))
            {
                return true;
            }
        }

        return false;
    }
}