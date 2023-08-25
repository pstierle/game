#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Sprite
{
public:
    SDL_FPoint position;
    SDL_Point spritePosition;
    int width;
    int height;
    int spriteHeight;
    int spriteWidth;
    bool staticPosition;

    Sprite(SDL_FPoint _position, SDL_Point _spritePosition, int _spriteWidth, int _spriteHeight, int _width, int _height);

    void render() const;
};

#endif