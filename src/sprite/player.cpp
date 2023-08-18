#include "player.hpp"
#include "constants.hpp"
#include "state.hpp"
#include "util.hpp"
#include <iostream>

extern State state;

Player::Player() : Sprite(START_POINT, {0, 1})
{
    health = 100;
    mouseX = -1;
    mouseY = -1;
    dx = 0;
    dy = 0;
}

Player::~Player()
{
}

void Player::update()
{
    const int speed = 5;
    gridPosition.x += dx * state.deltaTime * speed;
    gridPosition.y += dy * state.deltaTime * speed;
}

void Player::resetDirection(int keyCode)
{
    switch (keyCode)
    {
    case SDLK_w:
        dy = 0;
        break;
    case SDLK_a:
        dx = 0;
        break;
    case SDLK_s:
        dy = 0;
        break;
    case SDLK_d:
        dx = 0;
        break;
    }
}

void Player::updateDirection(int keyCode)
{
    switch (keyCode)
    {
    case SDLK_w:
        dy = -1;
        break;
    case SDLK_a:
        dx = -1;
        break;
    case SDLK_s:
        dy = 1;
        break;
    case SDLK_d:
        dx = 1;
        break;
    }

    // Field *nextField = nullptr;

    // for (int i = 0; i < GRID_COLS; ++i)
    // {
    //     for (int j = 0; j < GRID_ROWS; ++j)
    //     {
    //         SDL_FRect fieldRect = {state.map.fieldGrid[i][j].gridPosition.x * SPRITE_SIDE_LENGTH, state.map.fieldGrid[i][j].gridPosition.y * SPRITE_SIDE_LENGTH, SPRITE_SIDE_LENGTH, SPRITE_SIDE_LENGTH};
    //         if (nextPosition.x >= fieldRect.x && nextPosition.x <= fieldRect.x + fieldRect.w && nextPosition.y >= fieldRect.y && nextPosition.y <= fieldRect.y + fieldRect.h)
    //         {
    //             nextField = &state.map.fieldGrid[i][j];
    //         }
    //         break;
    //     }
    // }

    // if (nextField != nullptr)
    // {
    //     if (nextField->type == FieldType::NON_WALKABLE)
    //     {
    //         std::cout << "test" << std::endl;
    //     }
    // }

    // delete nextField;
}