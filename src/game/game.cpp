#include <cmath>
#include <iostream>
#include "map.hpp"
#include "game.hpp"
#include "player.hpp"
#include "state.hpp"
#include "constants.hpp"
#include "camera.hpp"

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

    state.window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);

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

    SDL_Surface *_spriteSurface = IMG_Load("sprite_sheet.png");
    SDL_Texture *_spriteTexture = SDL_CreateTextureFromSurface(state.renderer, _spriteSurface);

    state.spriteTexture = _spriteTexture;

    previousTime = SDL_GetTicks();

    gameInfoText = GameInfoText();

    state.map.initFields();
    state.map.initItems();

    state.camera.updatePosition({0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height)});

    running = true;
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
    if (e.type == SDL_KEYDOWN)
    {
        state.player.keyDown(e.key.keysym.sym);
    }
    if (e.type == SDL_KEYUP)
    {
        state.player.keyUp(e.key.keysym.sym);
    }
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            state.player.handleAttack();
        }
    }
}

void Game::update()
{
    Uint32 currentTime = SDL_GetTicks();
    state.deltaTime = (currentTime - previousTime) / 1000.0f;
    previousTime = currentTime;

    state.player.update();
    state.camera.update();
    state.map.update();
    gameInfoText.update();
}

void Game::render()
{
    SDL_RenderClear(state.renderer);

    state.map.render();
    state.player.render();
    gameInfoText.render();
    state.player.renderInventory();

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
