#include "player.hpp"
#include "constants.hpp"

Player::Player() : Sprite(START_POINT, {0, 1})
{
    health = 100;
    mouseX = -1;
    mouseY = -1;
}

Player::~Player()
{
}

void Player::update()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            gridPosition.y -= 1;
            break;
        case SDLK_a:
            gridPosition.x -= 1;
            break;
        case SDLK_s:
            gridPosition.y += 1;
            break;
        case SDLK_d:
            gridPosition.x += 1;
            break;
        }
    }
}