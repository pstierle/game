#include <iostream>
#include "game.hpp"
#include "state.hpp"
#include "fps_text.hpp"

extern State state;

Game::Game()
{
}
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

    state.window = SDL_CreateWindow("TD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (!state.window)
    {
        return false;
    }

    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED);

    if (!state.renderer)
    {
        return false;
    }

    state.font = TTF_OpenFont("Roboto.ttf", 12);

    if (!state.font)
    {
        return false;
    }

    running = true;
    previousTime = SDL_GetTicks();

    fpsText = FPSText();

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
}

void Game::update()
{
    Uint32 currentTime = SDL_GetTicks();
    state.deltaTime = (currentTime - previousTime) / 1000.0f;
    previousTime = currentTime;

    fpsText.update();
}

void Game::render()
{
    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 1);
    SDL_RenderClear(state.renderer);

    fpsText.render();

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