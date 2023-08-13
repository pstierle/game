#include <SDL2/SDL.h>
#include "game.hpp"

#ifdef __MINGW32__
#define SDL_MAIN_HANDLED
#endif

int SDL_main(int argc, char *argv[])
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
        game.listen_events();
        game.update();
        game.render();
    }

    game.destroy();

    return 0;
}