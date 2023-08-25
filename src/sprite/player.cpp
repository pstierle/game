#include "player.hpp"
#include "constants.hpp"
#include "state.hpp"
#include "util.hpp"
#include <iostream>
#include <vector>

extern State state;

Player::Player() : Sprite(START_POINT, {0, 1}, 32, 32, 64, 64)
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

bool Player::inRangeOfItem(Item item)
{
    double distance = Util::distancePoints(item.position, position);
    return distance < 20;
}

void Player::addToInventory(Item item)
{
    item.position.x = 0.0f;
    item.position.y = 0.0f;
    item.staticPosition = true;
    inventory.push_back(item);
}

void Player::update()
{
    const int speed = 600;

    int windowWidth, windowHeight;
    SDL_GetWindowSize(state.window, &windowWidth, &windowHeight);

    float destinationX = position.x + dx * state.deltaTime * speed;
    float destinationY = position.y + dy * state.deltaTime * speed;

    double maxX = state.map.fieldGrid[GRID_COLS - 1][GRID_ROWS - 1].initialPosition.x - width / 2;
    double maxY = state.map.fieldGrid[GRID_COLS - 1][GRID_ROWS - 1].initialPosition.y - height / 2;

    if (destinationX <= 0 || destinationX >= maxX)
    {
        return;
    }
    if (destinationY <= 0 || destinationY >= maxY)
    {
        return;
    }

    position.x += dx * state.deltaTime * speed;
    position.y += dy * state.deltaTime * speed;

    if (dy == 1)
    {
        spritePosition = {
            0, 0};
    }
    if (dy == -1)
    {
        spritePosition = {
            0, 1};
    }
    if (dx == 1)
    {
        spritePosition = {
            1, 0};
    }
    if (dx == -1)
    {
        spritePosition = {
            1, 1};
    }
}

void Player::keyUp(int keyCode)
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

void Player::keyDown(int keyCode)
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
    case SDLK_SPACE:
        for (size_t i = 0; i < state.map.items.size(); i++)
        {
            if (inRangeOfItem(state.map.items[i]))
            {
                addToInventory(state.map.items[i]);
                state.map.removeItem(i);
            }
        }
        break;
    }
}