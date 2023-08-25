#ifndef State_H
#define State_H

#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include <vector>
#include "map.hpp"
#include "camera.hpp"
#include "player.hpp"

struct State
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;
    SDL_Surface *spriteSurface;
    SDL_Texture *spriteTexture;
    Map map;
    Player player;
    Camera camera;
    float deltaTime;
};

#endif