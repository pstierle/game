
#include "global.hpp"

extern State state;

Sprite::Sprite() {}

Sprite::Sprite(TextureType _textureType, SDL_FPoint _position, int _width, int _height)
{
    width = _width;
    height = _height;
    setTexture(_textureType);
    position = _position;
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

SDL_FRect Sprite::positionRect()
{
    return {position.x, position.y, static_cast<float>(width), static_cast<float>(height)};
}
