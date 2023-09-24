#include "global.hpp"

extern State state;

Game::Game() {}
Game::~Game() {}

bool Game::setup()
{
    gameState = GameStateType::WEAPON_SELECTION;
    currentTurn = 0;
    previousTime = SDL_GetTicks();

    map = Map();
    map.setup();

    weaponMenu = WeaponMenu();
    selectedWeapon = nullptr;

    players.resize(3, Player());

    players[0] = Player(TextureType::PLAYER_BABY_YODA, "Yoda", {160.0f, 0.0f}, COLOR_RED);
    players[1] = Player(TextureType::PLAYER_MARIO, "Mario", {650.0f, 0.0f}, COLOR_GREEN);
    players[2] = Player(TextureType::PLAYER_SPONGEBOB, "Spongebob", {1150.0f, 0.0f}, COLOR_BLUE);

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
    if (e.type == SDL_KEYDOWN)
    {
    }
    if (e.type == SDL_KEYUP)
    {
    }
    if (e.type == SDL_MOUSEBUTTONUP)
    {
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            if (gameState == GameStateType::WEAPON_SELECTION)
            {
                weaponMenu.mouseClick();
            }
            else if (gameState == GameStateType::WEAPON_SELECTED)
            {
                if (selectedWeapon != nullptr)
                {
                    selectedWeapon->leftMouseUp();
                }
            }
        }
        if (e.button.button == SDL_BUTTON_RIGHT)
        {
            if (gameState == GameStateType::WEAPON_SELECTED)
            {
                setWeaponSelection();
            }
        }
    }
    if (e.type == SDL_MOUSEMOTION)
    {
        if (gameState == GameStateType::WEAPON_SELECTION)
        {
            weaponMenu.mouseMove(e.motion.x, e.motion.y);
        }
        if (gameState == GameStateType::WEAPON_SELECTED)
        {
            if (selectedWeapon != nullptr)
            {
                selectedWeapon->mouseMove(e.button.x, e.button.y);
            }
        }
    }
}

void Game::update()
{
    Uint32 currentTime = SDL_GetTicks();
    state.deltaTime = (currentTime - previousTime) / 1000.0f;
    previousTime = currentTime;

    map.update();

    weaponMenu.update();

    for (size_t i = 0; i < players.size(); ++i)
    {
        players[i].update();
    }

    if (selectedWeapon != nullptr)
    {
        selectedWeapon->update();
    }

    if (gameState == GameStateType::WEAPON_SELECTION || gameState == GameStateType::WEAPON_FIRING)
    {
        SDL_ShowCursor(SDL_ENABLE);
    }
    if (gameState == GameStateType::WEAPON_SELECTED)
    {
        SDL_ShowCursor(SDL_DISABLE);
    }
}

void Game::render()
{
    SDL_RenderClear(state.renderer);

    map.render();

    weaponMenu.render();

    for (size_t i = 0; i < players.size(); ++i)
    {
        players[i].render();
    }

    if (selectedWeapon != nullptr)
    {
        selectedWeapon->render();
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

void Game::setWeaponSelection()
{
    delete selectedWeapon;
    selectedWeapon = nullptr;
    gameState = GameStateType::WEAPON_SELECTION;
}

void Game::nextTurn()
{
    if (currentTurn == static_cast<int>(players.size()) - 1)
    {
        currentTurn = 0;
    }
    else
    {
        currentTurn++;
    }
}

Player Game::currentPlayer()
{
    return players[currentTurn];
}
