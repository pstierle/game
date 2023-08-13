#include "monster.hpp"
#include "state.hpp"
#include "util.hpp"
#include "constants.hpp"
#include <cmath>
#include <chrono>
#include <iostream>

extern State state;

Monster::Monster(SDL_FPoint _position, SDL_Point _spritePosition, long _delay) : Sprite(_position, _spritePosition)
{
    speed = 10;
    health = 100;
    visited.push_back(currentGridPosition());
    delay = _delay;

    auto currentTime = std::chrono::high_resolution_clock::now();
    currentTimeMillis = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();
}

void Monster::setSpeed(int _speed)
{
    speed = _speed;
}

void Monster::update()
{
    auto nextTime = std::chrono::high_resolution_clock::now();
    long nextTimeMillis = std::chrono::duration_cast<std::chrono::milliseconds>(nextTime.time_since_epoch()).count();

    if (nextTimeMillis - currentTimeMillis < delay)
    {
        return;
    }

    if (isEndPosition())
    {
        return;
    }

    int dx = 0;
    int dy = 0;
    double velocity = speed * state.deltaTime;

    const int possibleDX[4] = {-1, 0, 1, 0};
    const int possibleDY[4] = {0, -1, 0, 1};

    for (int i = 0; i < 4; ++i)
    {
        SDL_Point currentPosition = currentGridPosition();

        int newX = currentPosition.x;
        int newY = currentPosition.y;

        if (possibleDX[i] == -1)
        {
            newX = newX - 1;
        }

        if (possibleDX[i] == 1)
        {
            newX = newX + 1;
        }

        if (possibleDY[i] == -1)
        {
            newY = newY - 1;
        }

        if (possibleDY[i] == 1)
        {
            newY = newY + 1;
        }

        bool alreadyVisted = false;

        for (size_t j = 0; j < visited.size(); j++)
        {
            if (visited[j].x == newX && visited[j].y == newY)
            {
                alreadyVisted = true;
            }
        }

        if (!alreadyVisted && GRID[newY][newX] == 1)
        {
            dx = possibleDX[i];
            dy = possibleDY[i];
        }
    }

    if (dx != 0)
    {
        gridPosition.x += dx * velocity;
    }

    if (dy != 0)
    {
        gridPosition.y += dy * velocity;
    }

    visited.push_back(currentGridPosition());
}

SDL_Point Monster::currentGridPosition()
{
    return {
        static_cast<int>(std::floor(gridPosition.x)), static_cast<int>(std::floor(gridPosition.y))};
}

bool Monster::validGridPosition(int x, int y, int rows, int cols)
{
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

bool Monster::isEndPosition()
{
    return currentGridPosition().x == END_POINT.x && currentGridPosition().y == END_POINT.y;
}
