#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include "fps_text.hpp"

class Game
{
public:
    bool running;

    Game();
    ~Game();

    bool setup(int width, int height);
    void update();
    void listen_events();
    void render();
    void destroy();

private:
    Uint32 previousTime;
    FPSText fpsText;
};

#endif