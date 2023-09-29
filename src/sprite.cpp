
#include "global.hpp"

extern State state;

Sprite::Sprite() : Entity() {}

Sprite::Sprite(TextureType _textureType, SDL_FPoint _position, int _width, int _height) : Entity(_position, _width, _height)
{
    setTexture(_textureType);
}

void Sprite::render()
{
    SDL_Rect spriteSource = {0, 0, 16, 16};
    SDL_FRect positionDestination = positionRect();
    SDL_RenderCopyF(state.renderer, texture, &spriteSource, &positionDestination);
}

void Sprite::setTexture(TextureType _textureType)
{
    textureType = _textureType;
    texture = state.textureLoader.get(_textureType);
}
