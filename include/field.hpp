#ifndef FIELD_HPP
#define FIELD_HPP

#include "field_type.hpp"
#include "sprite.hpp"

class Field : public Sprite
{
public:
    FieldType type;
    Field();
    Field(SDL_FPoint _position, FieldType _type, SDL_Point _spritePosition);
};

#endif