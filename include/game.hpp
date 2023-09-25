#ifndef GAME_HPP
#define GAME_HPP

#include "global.hpp"

class Game
{
public:
    Uint32 previousTime;
    std::vector<Player> players;
    Player *lastPlayer;
    Map map;
    WeaponMenu weaponMenu;
    Weapon *selectedWeapon;
    GameStateType gameState;
    Text gameOverText;

    int currentTurn;
    bool running;
    bool gameOver;

    Game();
    ~Game();

    bool setup();
    void update();
    void listen_events();
    void render();
    void destroy();
    void setWeaponSelection();
    void nextTurn();
    void checkGameOver();
    Player currentPlayer();
};

#endif