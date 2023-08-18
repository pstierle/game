#include <cmath>
#include "map.hpp"
#include "game.hpp"
#include "player.hpp"
#include "state.hpp"
#include "constants.hpp"

extern State state;

Game::Game() {}
Game::~Game() {}

bool Game::setup(int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    if (TTF_Init() < 0)
    {
        return false;
    }

    state.window = SDL_CreateWindow("TD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);

    if (!state.window)
    {
        return false;
    }

    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED);

    if (!state.renderer)
    {
        return false;
    }

    state.font = TTF_OpenFont("Roboto.ttf", FONT_SIZE);

    if (!state.font)
    {
        return false;
    }

    SDL_Surface *_surface = IMG_Load("sprite_sheet.png");
    SDL_Texture *_texture = SDL_CreateTextureFromSurface(state.renderer, _surface);

    state.texture = _texture;

    running = true;
    previousTime = SDL_GetTicks();

    gameInfoText = GameInfoText();

    state.map.initFields();

    return true;
}

void Game::listen_events()
{
    SDL_Event e;
    SDL_PollEvent(&e);

    if (e.type == SDL_QUIT)
    {
        running = false;
    }

    if (e.type == SDL_MOUSEMOTION)
    {
        state.player.mouseX = e.motion.x;
        state.player.mouseY = e.motion.y;
    }

    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (e.button.button == SDL_BUTTON_LEFT)
        {
        }
    }
    if (e.type == SDL_WINDOWEVENT)
    {
        if (e.window.event == SDL_WINDOWEVENT_RESIZED)
        {
        }
    }
}

void Game::update()
{
    Uint32 currentTime = SDL_GetTicks();
    state.deltaTime = (currentTime - previousTime) / 1000.0f;
    previousTime = currentTime;
    gameInfoText.update();
    state.player.update();
}

void Game::render()
{
    SDL_RenderClear(state.renderer);

    state.map.render();
    gameInfoText.render();
    state.player.render();

    SDL_RenderPresent(state.renderer);
}

void Game::destroy()
{
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    TTF_Quit();
    SDL_Quit();
    running = false;
}
