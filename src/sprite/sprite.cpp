
#include "sprite.hpp"
#include "state.hpp"
#include "constants.hpp"

extern State state;

Sprite::Sprite(SDL_FPoint _gridPosition, SDL_Point _spritePosition)
{
    gridPosition = _gridPosition;
    spritePosition = _spritePosition;
}

Sprite::~Sprite()
{
}

void Sprite::render()
{
    SDL_Rect spriteSource = {spritePosition.x * SPRITE_SIDE_LENGTH, spritePosition.y * SPRITE_SIDE_LENGTH, SPRITE_SIDE_LENGTH, SPRITE_SIDE_LENGTH};
    SDL_FRect positionDestination = {gridPosition.x * SPRITE_SIDE_LENGTH, gridPosition.y * SPRITE_SIDE_LENGTH, SPRITE_SIDE_LENGTH, SPRITE_SIDE_LENGTH};
    SDL_RenderCopyF(state.renderer, state.texture, &spriteSource, &positionDestination);
}
