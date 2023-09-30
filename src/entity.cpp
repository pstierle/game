#include "global.hpp"

Entity::~Entity()
{
}

Entity::Entity()
{
    position = {0, 0};
    width = 0;
    height = 0;
}

Entity::Entity(SDL_FPoint _position, int _width, int _height)
{
    position = _position;
    width = _width;
    height = _height;
}

void Entity::render()
{
}

void Entity::update()
{
}

SDL_FRect Entity::positionRect()
{
    return {position.x, position.y, static_cast<float>(width), static_cast<float>(height)};
}

SDL_FPoint Entity::positionCenter()
{
    return {position.x + width / 2, position.y + height / 2};
}
