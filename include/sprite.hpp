#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "global.hpp"

class Sprite
{
public:
    SDL_FPoint position;
    SDL_Texture *texture;
    TextureType textureType;

    int width;
    int height;

    Sprite();
    Sprite(TextureType _textureType, SDL_FPoint _position, int _width, int _height);

    void setTexture(TextureType _textureType);
    void render();
    SDL_FRect positionRect();
    SDL_FPoint center();
};

#endif