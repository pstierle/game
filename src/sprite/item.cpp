#include "item.hpp"

Item::Item(SDL_FPoint _position, SDL_Point _spritePosition, int _spriteWidth, int _spriteHeight, int _width, int _height, ItemType _type) : Sprite(_position, _spritePosition, _spriteWidth, _spriteHeight, _width, _height)
{
    type = _type;
}
