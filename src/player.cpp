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
    healthText = Text({0, 0}, "100", color);
    nameText.center = true;
    healthText.center = true;
    dy = 400;
    dx = 0;
    credits = 100;
    health = 100;
}

void Player::render()
{
    renderModel();
    renderInfoText();
}

void Player::update()
{
    updatePosition();
    updateInfoText();
}

SDL_FRect Player::positionRect()
{
    return {position.x, position.y, 32, 32};
}

void Player::updatePosition()
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
}
void Player::updateInfoText()
{
    nameText.position = position;
    nameText.position.y -= 46;
    nameText.position.x += 16;

    healthText.position = position;
    healthText.position.y -= 22;
    healthText.position.x += 16;
    healthText.text = std::to_string(health);
}

void Player::renderModel()
{
    SDL_Rect spriteSource = {0, 0, 64, 64};
    SDL_FRect positionDestination = {position.x, position.y, 32, 32};
    SDL_RenderCopyF(state.renderer, texture, &spriteSource, &positionDestination);
}
void Player::renderInfoText()
{
    SDL_FRect nameBackGroundRect = {nameText.position.x - 4 - static_cast<float>(nameText.width) / 2, nameText.position.y, static_cast<float>(nameText.width) + 8, 20.0f};
    Util::drawRectangle(nameBackGroundRect, COLOR_GREY, color, 2);

    SDL_FRect healthBackGroundRect = {healthText.position.x - 4 - static_cast<float>(healthText.width) / 2, healthText.position.y, static_cast<float>(healthText.width) + 8, 20.0f};
    Util::drawRectangle(healthBackGroundRect, COLOR_GREY, color, 2);

    nameText.render();
    healthText.render();
}
