#include "field.hpp"
#include "state.hpp"
#include "util.hpp"
#include "constants.hpp"

extern State state;

Field::Field() : Sprite({}, {})
{
}

Field::Field(SDL_FPoint _position, FieldType _type, SDL_Point _spritePosition) : Sprite(_position, _spritePosition)
{
    type = _type;
}
