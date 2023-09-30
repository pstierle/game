#include "global.hpp"

#ifdef __MINGW32__
#define SDL_MAIN_HANDLED
#endif

extern State state;

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    state.window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 960, SDL_WINDOW_RESIZABLE);
    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED);
    state.font = TTF_OpenFont("font.ttf", FONT_SIZE);
    state.fontLarge = TTF_OpenFont("font.ttf", FONT_SIZE_LARGE);
    state.textureLoader.init();
    state.game = Game();
    state.game.setup();

    while (state.game.running)
    {
        state.game.listen_events();
        state.game.update();
        state.game.render();
    }

    state.game.destroy();

    return 0;
}