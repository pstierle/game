#ifndef State_H
#define State_H

#include "global.hpp"

struct State
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;
    TextureLoader textureLoader;
    Game game;
    float deltaTime;
};

#endif