#include "monster.hpp"
#include "state.hpp"
#include "util.hpp"
#include "constants.hpp"
#include <iostream>
#include <cmath>

extern State state;

Monster::Monster(SDL_FPoint _position, SDL_Point _spritePosition) : Sprite(_position, _spritePosition)
{
    speed = 4;
    visited.push_back(currentGridPosition());
}

void Monster::update()
{

    if (gridPosition.x == END_POINT.x && gridPosition.y == END_POINT.y)
    {
        std::cout << "ENDDD" << std::endl;

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

        for (int j = 0; j < visited.size(); j++)
        {
            if (visited[j].x == newX && visited[j].y == newY)
            {
                alreadyVisted = true;
            }
        }

        if (!alreadyVisted && newX >= 0, newY >= 0 && GRID[newY][newX] == 1)
        {
            dx = possibleDX[i];
            dy = possibleDY[i];
        }
    }

    if (dx > 0)
    {
        gridPosition.x = gridPosition.x + velocity;
    }

    if (dy > 0)
    {
        gridPosition.y = gridPosition.y + velocity;
    }

    if (dx < 0)
    {
        gridPosition.x = gridPosition.x - velocity;
    }

    if (dy < 0)
    {
        gridPosition.y = gridPosition.y - velocity;
    }
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
