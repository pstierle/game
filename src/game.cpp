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

    players[0] = Player(TextureType::PLAYER_HULK, "Hulk", {650.0f, 0.0f}, COLOR_GREEN, 44, 44, WeaponType::HULK);
    players[1] = Player(TextureType::PLAYER_SUPERMAN, "Superman", {1150.0f, 0.0f}, COLOR_BLUE, 32, 44, WeaponType::SUPERMAN);
    players[2] = Player(TextureType::PLAYER_IRONMAN, "Ironman", {250.0f, 0.0f}, COLOR_RED, 31, 44, WeaponType::IRONMAN);

    gameOverText = Text({0, 0}, "");
    gameOverText.center = true;

    gameOver = false;
    lastPlayer = nullptr;
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
    if (gameOver)
    {
        int windowWidth, windowHeight;
        SDL_GetWindowSize(state.window, &windowWidth, &windowHeight);

        gameOverText.position = {static_cast<float>(windowWidth) / 2, static_cast<float>(windowHeight) / 2};

        if (lastPlayer == nullptr)
        {
            gameOverText.text = "Game over no one won.";
        }
        else
        {
            gameOverText.text = "Game over " + lastPlayer->name + " won.";
        }
        return;
    }

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

    checkGameOver();
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

    if (gameOver)
    {
        int windowWidth, windowHeight;
        SDL_GetWindowSize(state.window, &windowWidth, &windowHeight);

        SDL_SetRenderDrawBlendMode(state.renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 128);
        SDL_Rect shadeRect = {0, 0, windowWidth, windowHeight};
        SDL_RenderFillRect(state.renderer, &shadeRect);
        SDL_SetRenderDrawBlendMode(state.renderer, SDL_BLENDMODE_NONE);

        gameOverText.render();
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

void Game::checkGameOver()
{
    std::vector<int> playersToRemove;

    for (size_t i = 0; i < players.size(); ++i)
    {
        if (players[i].health <= 0)
        {
            playersToRemove.push_back(i);
        }
    }

    for (int i = playersToRemove.size() - 1; i >= 0; --i)
    {
        players.erase(players.begin() + playersToRemove[i]);
    }

    if (players.size() == 0)
    {
        gameOver = true;
        return;
    }

    if (players.size() == 1)
    {
        lastPlayer = &players[0];
        gameOver = true;
        return;
    }
}
