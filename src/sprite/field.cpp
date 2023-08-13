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

void Field::update()
{
    if (type == FieldType::PLACEABLE)
    {
        SDL_FRect positionDestination = {gridPosition.x * SPRITE_SIDE_LENGTH, gridPosition.y * SPRITE_SIDE_LENGTH, SPRITE_SIDE_LENGTH, SPRITE_SIDE_LENGTH};

        if (Util::pointInRect(state.mouseX, state.mouseY, positionDestination))
        {
            highlight = true;
        }
        else
        {
            highlight = false;
        }
    }
}
