#include <cmath>
#include "map.hpp"
#include "game.hpp"
#include "state.hpp"
#include "constants.hpp"

extern State state;

Game::Game() {}
Game::~Game() {}

void Game::startWave()
{
    state.waveCount++;
    int monsterCount = state.waveCount * 1000;

    for (int i = 0; i < monsterCount; ++i)
    {
        Monster *monster = new Monster(START_POINT, {0, 1}, i * 200);
        monsters.push_back(monster);
    }
}

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
    state.playerHealth = 100;

    running = true;
    previousTime = SDL_GetTicks();

    gameInfoText = GameInfoText();

    waveButton = Button({700, 0, 120, 32}, "Start Round");

    state.map = new Map();

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
        if (roundRunning())
        {
            state.mouseX = -1;
            state.mouseY = -1;
        }
        else
        {
            state.mouseX = e.motion.x;
            state.mouseY = e.motion.y;
        }
    }

    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            int mouseX = e.button.x;
            int mouseY = e.button.y;

            if (!roundRunning())
            {
                if (waveButton.isClicked(mouseX, mouseY))
                {
                    startWave();
                }
            }
        }
    }
    if (e.type == SDL_WINDOWEVENT)
    {
        if (e.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            // int newWidth = e.window.data1;
            // int newHeight = e.window.data2;
        }
    }
}

void Game::update()
{
    Uint32 currentTime = SDL_GetTicks();
    state.deltaTime = (currentTime - previousTime) / 1000.0f;
    previousTime = currentTime;
    state.map->update();
    gameInfoText.update();

    for (auto it = monsters.begin(); it != monsters.end();)
    {
        if ((*it)->isEndPosition())
        {
            state.playerHealth--;
            delete *it;
            it = monsters.erase(it);
        }
        else if ((*it)->health <= 0)
        {
            // death anim
            delete *it;
            it = monsters.erase(it);
        }
        else
        {
            (*it)->update();
            ++it;
        }
    }
}

void Game::render()
{
    SDL_RenderClear(state.renderer);

    state.map->render();
    gameInfoText.render();

    for (Monster *monster : monsters)
    {
        monster->render();
    }

    if (!roundRunning())
    {
        waveButton.render();
    }

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

bool Game::roundRunning()
{
    return monsters.size() > 0;
}