#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "global.hpp"

class Sprite : public Entity
{
public:
    SDL_Texture *texture;
    TextureType textureType;

    Sprite();
    Sprite(TextureType _textureType, SDL_FPoint _position, int _width, int _height);
    Sprite(SDL_Texture *_texture, SDL_FPoint _position, int _width, int _height);

    void setTexture(TextureType _textureType);
    void render() override;
};

#endif