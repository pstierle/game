#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Sprite
{
public:
    SDL_FPoint gridPosition;
    SDL_Point spritePosition;
    bool highlight;

    Sprite(SDL_FPoint _gridPosition, SDL_Point _spritePosition);
    ~Sprite();

    void render();
};

#endif