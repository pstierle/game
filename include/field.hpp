#ifndef FIELD_HPP
#define FIELD_HPP

#include "field_type.hpp"
#include "sprite.hpp"

class Field : public Sprite
{
public:
    SDL_FPoint initialPosition;
    Field();
    Field(SDL_FPoint _position, SDL_Point _spritePosition);
};

#endif