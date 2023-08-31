#ifndef ITEM_HPP
#define ITEM_HPP

#include <SDL2/SDL.h>
#include "sprite.hpp"
#include "item_type.hpp"

class Item : public Sprite
{
public:
    ItemType type;

    Item(SDL_FPoint _position, SDL_Point _spritePosition, int _spriteWidth, int _spriteHeight, int _width, int _height, ItemType _type);
};

#endif