#include "player.hpp"
#include "constants.hpp"
#include "state.hpp"
#include "util.hpp"
#include "item_type.hpp"
#include <iostream>
#include <vector>

extern State state;

Player::Player() : Sprite(START_POINT, {0, 1}, 32, 32, 64, 64)
{
    health = 100;
    mouseX = -1;
    mouseY = -1;
    currentDirection = {0, 0};
    lastDirection = {0, 1};
    selectedItemIndex = -1;
    direction = Direction::UP;

    for (int i = 0; i < PLAYER_MAX_ITEMS; i++)
    {
        Sprite inventorySlot({0, 0}, {3, 1}, 32, 32, 48, 48);
        inventorySlot.staticPosition = true;
        inventorySlots.push_back(inventorySlot);
    }
}

Player::~Player()
{
}

bool Player::inRangeOfItem(Item item)
{
    double distance = Util::distancePoints(item.position, position);
    return distance < 40;
}

void Player::addToInventory(Item item)
{
    item.staticPosition = true;
    inventory.push_back(item);
}

void Player::selectItem(int index)
{
    if (index == selectedItemIndex)
    {
        selectedItemIndex = -1;
    }
    else
    {
        selectedItemIndex = index;
    }
}

void Player::renderInventory()
{
    int windowWidth, windowHeight;
    SDL_GetWindowSize(state.window, &windowWidth, &windowHeight);
    int inventorySlotsWidth = PLAYER_MAX_ITEMS * 48;

    for (int i = 0; i < PLAYER_MAX_ITEMS; i++)
    {
        int offset = inventorySlots[i].width + 4;
        inventorySlots[i].position.x = (windowWidth / 2) + (i * offset) - (inventorySlotsWidth / 2);
        inventorySlots[i].position.y = windowHeight - offset;
        inventorySlots[i].render();
        if (i == selectedItemIndex)
        {
            SDL_FRect selectedItemRect = {inventorySlots[i].position.x, inventorySlots[i].position.y, static_cast<float>(inventorySlots[i].width), static_cast<float>(inventorySlots[i].height)};
            SDL_SetRenderDrawColor(state.renderer, 255, 0, 0, 255);
            SDL_RenderDrawRectF(state.renderer, &selectedItemRect);
        }
    }

    for (size_t i = 0; i < inventory.size(); i++)
    {
        inventory[i].position = inventorySlots[i].position;
        inventory[i].render();
    }

    SDL_Point targetDirection = currentDirection;
    if (currentDirection.x == 0 && currentDirection.y == 0)
    {
        targetDirection = lastDirection;
    }

    SDL_FRect attackTargetRect = {position.x + 16 - state.camera.position.x, position.y + 16 - state.camera.position.y, 32, 32};

    if (targetDirection.x == 1)
    {
        attackTargetRect.x += 32;
    }

    if (targetDirection.x == -1)
    {
        attackTargetRect.x -= 32;
    }

    if (targetDirection.y == 1)
    {
        attackTargetRect.y += 32;
    }

    if (targetDirection.y == -1)
    {
        attackTargetRect.y -= 32;
    }

    SDL_SetRenderDrawColor(state.renderer, 255, 0, 0, 255);
    SDL_RenderDrawRectF(state.renderer, &attackTargetRect);
}

void Player::update()
{
    updatePlayerPosition();
    updatePlayerSprite();
}

void Player::handleAttack()
{
    animationStartTime = SDL_GetTicks();
}

void Player::updatePlayerPosition()
{
    const int speed = 400;

    int windowWidth, windowHeight;
    SDL_GetWindowSize(state.window, &windowWidth, &windowHeight);

    float destinationX = position.x + currentDirection.x * state.deltaTime * speed;
    float destinationY = position.y + currentDirection.y * state.deltaTime * speed;

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

    position.x += currentDirection.x * state.deltaTime * speed;
    position.y += currentDirection.y * state.deltaTime * speed;
}

void Player::updatePlayerSprite()
{
    if (SDL_GetTicks() - animationStartTime < 1000)
    {
        if (lastDirection.x == 0 && lastDirection.y == 1)
        {
            spritePosition = {
                2, 2};
        }
        if (lastDirection.x == 0 && lastDirection.y == -1)
        {
            spritePosition = {
                2, 3};
        }
        if (lastDirection.x == -1 && lastDirection.y == 0)
        {
            spritePosition = {
                3, 2};
        }
        if (lastDirection.x == 1 && lastDirection.y == 0)
        {
            spritePosition = {
                3, 3};
        }
        return;
    }

    ItemType selectedItemType = ItemType::NONE;

    for (size_t i = 0; i < inventory.size(); i++)
    {
        if (i == static_cast<size_t>(selectedItemIndex))
        {
            selectedItemType = inventory[i].type;
        }
    }

    SDL_Point targetDirection = currentDirection;
    if (currentDirection.x == 0 && currentDirection.y == 0)
    {
        targetDirection = lastDirection;
    }

    if (selectedItemType == ItemType::SWORD)
    {

        if (targetDirection.y == 1)
        {
            spritePosition = {
                0, 2};
        }
        if (targetDirection.y == -1)
        {
            spritePosition = {
                0, 3};
        }
        if (targetDirection.x == 1)
        {
            spritePosition = {
                1, 2};
        }
        if (targetDirection.x == -1)
        {
            spritePosition = {
                1, 3};
        }
    }
    else
    {
        if (targetDirection.y == 1)
        {
            spritePosition = {
                0, 0};
        }
        if (targetDirection.y == -1)
        {
            spritePosition = {
                0, 1};
        }
        if (targetDirection.x == 1)
        {
            spritePosition = {
                1, 0};
        }
        if (targetDirection.x == -1)
        {
            spritePosition = {
                1, 1};
        }
    }
}

void Player::keyUp(int keyCode)
{
    switch (keyCode)
    {
    case SDLK_w:
        lastDirection = currentDirection;
        currentDirection = {currentDirection.x, 0};
        break;
    case SDLK_a:
        lastDirection = currentDirection;
        currentDirection = {0, currentDirection.y};
        break;
    case SDLK_s:
        lastDirection = currentDirection;
        currentDirection = {currentDirection.x, 0};
        break;
    case SDLK_d:
        lastDirection = currentDirection;
        currentDirection = {0, currentDirection.y};
        break;
    }
}

void Player::keyDown(int keyCode)
{
    switch (keyCode)
    {
    case SDLK_w:
        currentDirection = {currentDirection.x, -1};
        break;
    case SDLK_a:
        currentDirection = {-1, currentDirection.y};
        break;
    case SDLK_s:
        currentDirection = {currentDirection.x, 1};
        break;
    case SDLK_d:
        currentDirection = {1, currentDirection.y};
        break;
    case SDLK_SPACE:
        for (size_t i = 0; i < state.map.items.size(); i++)
        {
            if (inRangeOfItem(state.map.items[i]) && inventory.size() < PLAYER_MAX_ITEMS)
            {
                addToInventory(state.map.items[i]);
                state.map.removeItem(i);
            }
        }
        break;
    case SDLK_1:
        selectItem(0);
        break;
    case SDLK_2:
        selectItem(1);
        break;
    case SDLK_3:
        selectItem(2);
        break;
    case SDLK_4:
        selectItem(3);
        break;
    case SDLK_5:
        selectItem(4);
        break;
    }
}