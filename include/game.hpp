#ifndef GAME_HPP
#define GAME_HPP

#include "global.hpp"

class Game
{
public:
    Uint32 previousTime;
    std::vector<Player> players;
    Map map;
    WeaponMenu weaponMenu;
    Weapon *selectedWeapon;
    GameStateType gameState;

    int currentTurn;
    bool running;

    Game();
    ~Game();

    bool setup();
    void update();
    void listen_events();
    void render();
    void destroy();
    void setWeaponSelection();
    void nextTurn();
    Player currentPlayer();
};

#endif