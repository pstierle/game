#include "global.hpp"

extern State state;

Player::Player()
{
}

Player::Player(TextureType _textureType, std::string _name, SDL_FPoint _position, SDL_Color _color)
{
    textureType = _textureType;
    texture = state.textureLoader.get(_textureType);
    name = _name;
    position = _position;
    color = _color;
    nameText = Text({0, 0}, name, color);
    nameText.center = true;
    dy = 400;
    dx = 0;
    credits = 100;
    health = 100;
}

void Player::render()
{
    // player model
    SDL_Rect spriteSource = {0, 0, 64, 64};
    SDL_FRect positionDestination = {position.x, position.y, 32, 32};
    SDL_RenderCopyF(state.renderer, texture, &spriteSource, &positionDestination);

    // render text
    nameText.render();
}

void Player::update()
{
    bool yAxisIntersection = false;

    for (int i = 0; i < GRID_ROWS; ++i)
    {
        for (int j = 0; j < GRID_COLS; ++j)
        {
            if (state.game.map.tileGrid[i][j].textureType == TextureType::ROCK)
            {
                SDL_FRect rockRect = state.game.map.tileGrid[i][j].positionRect();
                SDL_FRect playerRect = {position.x, position.y, 32, 32};

                if (SDL_HasIntersectionF(&playerRect, &rockRect))
                {
                    if (playerRect.y + playerRect.h < rockRect.y + rockRect.h && dy > 0)
                    {
                        dy = 0;
                        yAxisIntersection = true;
                    }
                    else if (playerRect.y > rockRect.y && dy < 0)
                    {
                        dy = 0;
                        yAxisIntersection = true;
                    }
                    else if (playerRect.x + playerRect.w < rockRect.x + rockRect.w && dx > 0)
                    {
                        dx = 0;
                    }
                    else if (playerRect.x > rockRect.x && dx < 0)
                    {
                        dx = 0;
                    }
                }
            }
        }
    }

    if (dx > 0)
    {
        position.x += dx * state.deltaTime;
    }
    if (dy > 0)
    {
        position.y += dy * state.deltaTime;
    }

    if (yAxisIntersection == false)
    {
        dy += GRAVITY * state.deltaTime;
    }

    // text position
    nameText.position = position;
    nameText.position.y -= 20;
    nameText.position.x += 16;
}

SDL_FRect Player::positionRect()
{
    return {position.x, position.y, 32, 32};
}
