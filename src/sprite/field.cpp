#include "field.hpp"
#include "util.hpp"
#include "constants.hpp"
#include "state.hpp"

extern State state;

Field::Field() : Sprite({}, {}, 0, 0, 0, 0)
{
}

Field::Field(SDL_FPoint _position, SDL_Point _spritePosition) : Sprite(_position, _spritePosition, 32, 32, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH)
{
    initialPosition = _position;
}
