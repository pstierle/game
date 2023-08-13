#include "map.hpp"
#include "constants.hpp"
#include <iostream>

Map::Map()
{
    fieldGrid.resize(GRID_COLS, std::vector<Field>(GRID_ROWS, Field()));

    for (int i = 0; i < GRID_COLS; ++i)
    {
        for (int j = 0; j < GRID_ROWS; ++j)
        {
            if (GRID[j][i] == 1)
            {
                Field field({static_cast<float>(i), static_cast<float>(j)}, FieldType::NON_PLACEABLE, {1, 0});
                fieldGrid[i][j] = field;
            }
            if (GRID[j][i] == 0)
            {
                Field field({static_cast<float>(i), static_cast<float>(j)}, FieldType::PLACEABLE, {0, 0});
                fieldGrid[i][j] = field;
            }
        }
    }
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
}

void Map::update()
{
    for (int i = 0; i < GRID_COLS; ++i)
    {
        for (int j = 0; j < GRID_ROWS; ++j)
        {
            fieldGrid[i][j].update();
        }
    }
}