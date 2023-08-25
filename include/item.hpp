#ifndef ITEM_HPP
#define ITEM_HPP

#include <SDL2/SDL.h>
#include "sprite.hpp"

class Item : public Sprite
{
public:
    Item(SDL_FPoint _position, SDL_Point _spritePosition, int _spriteWidth, int _spriteHeight, int _width, int _height);
};

#endif