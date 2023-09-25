#include "global.hpp"

#ifdef __MINGW32__
#define SDL_MAIN_HANDLED
#endif

extern State state;

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 1;
    }

    if (TTF_Init() < 0)
    {
        return 1;
    }

    state.window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 960, SDL_WINDOW_RESIZABLE);

    if (!state.window)
    {
        return 1;
    }

    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED);

    if (!state.renderer)
    {
        return 1;
    }

    state.font = TTF_OpenFont("Roboto.ttf", FONT_SIZE);

    if (!state.font)
    {
        return 1;
    }

    state.textureLoader.init();

    state.game = Game();

    bool setup = state.game.setup();

    if (!setup)
    {
        return 1;
    }

    while (state.game.running)
    {
        state.game.listen_events();
        state.game.update();
        state.game.render();
    }

    state.game.destroy();

    return 0;
}