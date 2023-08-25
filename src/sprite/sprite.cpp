
#include "sprite.hpp"
#include "state.hpp"
#include "constants.hpp"

extern State state;

Sprite::Sprite(SDL_FPoint _position, SDL_Point _spritePosition, int _spriteWidth, int _spriteHeight, int _width, int _height)
{
    position = _position;
    spritePosition = _spritePosition;
    width = _width;
    height = _height;
    spriteWidth = _spriteWidth;
    spriteHeight = _spriteHeight;
}

void Sprite::render() const
{
    SDL_Rect spriteSource = {spritePosition.x * spriteWidth, spritePosition.y * spriteHeight, spriteWidth, spriteHeight};
    SDL_FRect positionDestination = {position.x - state.camera.position.x, position.y - state.camera.position.y, static_cast<float>(width), static_cast<float>(height)};
    if (staticPosition)
    {
        positionDestination.x = positionDestination.x + state.camera.position.x;
        positionDestination.y = positionDestination.y + state.camera.position.y;
    }
    SDL_RenderCopyF(state.renderer, state.spriteTexture, &spriteSource, &positionDestination);
    // SDL_SetRenderDrawColor(state.renderer, 255, 0, 0, 255);
    // SDL_RenderDrawRectF(state.renderer, &positionDestination);
}
