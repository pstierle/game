#ifndef State_H
#define State_H

#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include <vector>
#include "map.hpp"

struct State
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;
    SDL_Surface *surface;
    SDL_Texture *texture;
    Map *map;
    int mouseX;
    int mouseY;
    int waveCount;
    float deltaTime;
};

#endif