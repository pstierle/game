#include "map.hpp"
#include "constants.hpp"
#include "state.hpp"
#include "text.hpp"
#include "sword.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

extern State state;

Map::Map()
{
}

void Map::initFields()
{
    fieldGrid.resize(GRID_COLS, std::vector<Field>(GRID_ROWS, Field()));

    for (int i = 0; i < GRID_COLS; ++i)
    {
        for (int j = 0; j < GRID_ROWS; ++j)
        {
            if (GRID[j][i] == 1)
            {
                SDL_Point dirt = {};

                if (GRID[j - 1][i] == 1 || GRID[j + 1][i] == 1)
                {
                    dirt = {3, 0};
                }
                else
                {
                    dirt = {5, 0};
                }
                Field field({static_cast<float>(i) * GRID_SIDE_LENGTH, static_cast<float>(j) * GRID_SIDE_LENGTH}, dirt);
                fieldGrid[i][j] = field;
                width = static_cast<float>(i) * GRID_SIDE_LENGTH;
                height = static_cast<float>(j) * GRID_SIDE_LENGTH;
            }
            if (GRID[j][i] == 0)
            {
                int random = (std::rand() % 2 == 0) ? 2 : 4;

                Field field({static_cast<float>(i) * GRID_SIDE_LENGTH, static_cast<float>(j) * GRID_SIDE_LENGTH}, {random, 0});
                fieldGrid[i][j] = field;
                width = static_cast<float>(i) * GRID_SIDE_LENGTH;
                height = static_cast<float>(j) * GRID_SIDE_LENGTH;
            }
        }
    }
}

void Map::initItems()
{
    Sword sword({30.0f, 30.0f});
    items.push_back(sword);

    Sword sword1({120.0f, 60.0f});
    items.push_back(sword1);
}

void Map::render()
{

    for (int i = 0; i < GRID_COLS; ++i)
    {
        for (int j = 0; j < GRID_ROWS; ++j)
        {
            fieldGrid[i][j].render();
        }
    }

    for (const auto item : items)
    {
        item.render();
    }
}

void Map::removeItem(size_t index)
{
    auto itemToRemove = items.begin() + index;

    if (itemToRemove != items.end())
    {
        items.erase(itemToRemove);
    }
}

void Map::update()
{

    for (int i = 0; i < GRID_COLS; ++i)
    {
        for (int j = 0; j < GRID_ROWS; ++j)
        {
            float initialX = fieldGrid[i][j].initialPosition.x;
            float initialY = fieldGrid[i][j].initialPosition.y;

            fieldGrid[i][j].position.x = initialX - state.camera.position.x;
            fieldGrid[i][j].position.y = initialY - state.camera.position.y;
        }
    }
}
