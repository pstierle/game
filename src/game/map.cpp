#include "map.hpp"
#include "constants.hpp"
#include "state.hpp"
#include "text.hpp"
#include "sword.hpp"
#include <iostream>

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
                Field field({static_cast<float>(i) * GRID_SIDE_LENGTH, static_cast<float>(j) * GRID_SIDE_LENGTH}, FieldType::DIRT, {3, 0});
                fieldGrid[i][j] = field;
                width = static_cast<float>(i) * GRID_SIDE_LENGTH;
                height = static_cast<float>(j) * GRID_SIDE_LENGTH;
            }
            if (GRID[j][i] == 0)
            {
                Field field({static_cast<float>(i) * GRID_SIDE_LENGTH, static_cast<float>(j) * GRID_SIDE_LENGTH}, FieldType::GRASS, {2, 0});
                fieldGrid[i][j] = field;
                width = static_cast<float>(i) * GRID_SIDE_LENGTH;
                height = static_cast<float>(j) * GRID_SIDE_LENGTH;
            }
        }
    }
}

void Map::initItems()
{
    items.resize(1, Item({}, {}, 0, 0, 0, 0));
    Sword sword({30.0f, 30.0f});
    items[0] = sword;
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
