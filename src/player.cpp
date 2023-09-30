#include "global.hpp"

extern State state;

Player::Player() : Entity()
{
}

Player::Player(TextureType _textureType, std::string _name, SDL_FPoint _position, SDL_Color _color, int _width, int _height, WeaponType _specialWeaponType) : Entity(_position, _width, _height)
{
    textureType = _textureType;
    texture = state.textureLoader.get(_textureType);
    name = _name;
    color = _color;
    nameText = Text({0, 0}, name, color, false);
    healthText = Text({0, 0}, "100", color, false);
    nameText.center = true;
    healthText.center = true;
    credits = 100;
    health = 100;
    bounceStart = 0;
    xVelocity = 0;
    yVelocity = 0;
    specialWeaponType = _specialWeaponType;
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

void Player::updatePosition()
{
    if (SDL_GetTicks() - bounceStart < 300 && bounceStart != 0)
    {
        float speed = 300 - (SDL_GetTicks() - bounceStart);
        float radians = launchAngle * (3.14159265359f / 180.0f);
        xVelocity = speed * cos(radians) * -1;
    }
    else
    {
        xVelocity = 0;
    }

    bool yAxisIntersection = false;
    bool xAxisIntersection = false;

    for (int i = 0; i < GRID_ROWS; ++i)
    {
        for (int j = 0; j < GRID_COLS; ++j)
        {
            if (state.game.map.tileGrid[i][j].textureType == TextureType::ROCK)
            {
                SDL_FRect rockRect = state.game.map.tileGrid[i][j].positionRect();
                SDL_FRect playerRect = positionRect();

                if (SDL_HasIntersectionF(&playerRect, &rockRect))
                {
                    if (playerRect.y + playerRect.h < rockRect.y + rockRect.h)
                    {
                        yAxisIntersection = true;
                    }
                    else if (playerRect.y > rockRect.y)
                    {
                        yAxisIntersection = true;
                    }
                    if (playerRect.x + playerRect.w < rockRect.x + rockRect.w)
                    {
                        xAxisIntersection = true;
                    }
                    else if (playerRect.x > rockRect.x)
                    {
                        xAxisIntersection = true;
                    }
                }
            }
        }
    }

    if (!yAxisIntersection)
    {
        if (yVelocity > 0 || yVelocity < 0)
        {
            position.y += GRAVITY * yVelocity * state.deltaTime;
        }
        else
        {
            position.y += GRAVITY * state.deltaTime;
        }
    }
    if (!xAxisIntersection)
    {
        if (xVelocity > 0 || xVelocity < 0)
        {
            position.x += xVelocity * state.deltaTime;
        }
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
    SDL_Rect spriteSource = {0, 0, width, height};
    SDL_FRect positionDestination = {position.x, position.y, static_cast<float>(width), static_cast<float>(height)};
    SDL_RenderCopyF(state.renderer, texture, &spriteSource, &positionDestination);
}

void Player::renderInfoText()
{
    SDL_FRect nameBackGroundRect = {nameText.position.x - 4 - static_cast<float>(nameText.textWidth) / 2, nameText.position.y, static_cast<float>(nameText.textWidth) + 8, static_cast<float>(nameText.textHeight)};
    Util::drawRectangle(nameBackGroundRect, COLOR_GREY, color, 1);

    SDL_FRect healthBackGroundRect = {healthText.position.x - 4 - static_cast<float>(healthText.textWidth) / 2, healthText.position.y, static_cast<float>(healthText.textWidth) + 8, static_cast<float>(healthText.textHeight)};
    Util::drawRectangle(healthBackGroundRect, COLOR_GREY, color, 1);

    nameText.render();
    healthText.render();
}

void Player::damagePlayer(int damage)
{
    health -= damage;
}

void Player::bounceBack(float _launchAngle)
{
    launchAngle = _launchAngle;
    bounceStart = SDL_GetTicks();
}
