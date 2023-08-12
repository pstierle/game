#ifndef State_H
#define State_H

#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include <vector>

struct State
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;
    float deltaTime;
};

#endif