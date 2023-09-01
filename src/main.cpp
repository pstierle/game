#include <SDL2/SDL.h>
#include "game.hpp"

#ifdef __MINGW32__
#define SDL_MAIN_HANDLED
#endif

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    Game game;

    bool setup = game.setup(1280, 960);

    if (!setup)
    {
        return 1;
    }

    while (game.running)
    {
        game.update();
        game.listen_events();
        game.render();
    }

    game.destroy();

    return 0;
}