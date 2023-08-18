#ifndef State_H
#define State_H

#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include <vector>
#include "map.hpp"
#include "player.hpp"

struct State
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Surface *playerSurface;
    SDL_Texture *playerTexture;
    Map map;
    Player player;
    float deltaTime;
};

#endif