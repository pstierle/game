#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "global.hpp"

class Weapon
{
public:
    SDL_Point mousePosition;

    int cost;
    float launchAngle;

    Weapon(int _cost);

    virtual ~Weapon() {}
    virtual void render();
    virtual void update();
    virtual void leftMouseUp();
    void mouseMove(int x, int y);
    void fireWeapon();
    void updateLaunchAngle(SDL_FPoint start);
    bool intersectsSolidTile(SDL_FRect rect);
    bool intersectsPlayer(SDL_FRect rect, bool ignoreCurrentPlayer);
    void damagePlayersInRange(SDL_FRect rect, int damage, bool ignoreCurrentPlayer);
    void explodeSolidTilesInRange(SDL_FRect rect);
    void renderAimDirection(SDL_FPoint start, float length);
};

#endif