#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include "game_info_text.hpp"
#include "monster.hpp"
#include "button.hpp"

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
    void startWave();

private:
    Uint32 previousTime;
    GameInfoText gameInfoText;
    std::vector<Monster *> monsters;
    Button waveButton;
};

#endif