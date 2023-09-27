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
    bool intersectsSolidTile(SDL_FRect _rect);
    void damagePlayersInRange(SDL_FRect _rect, int damage);
    void explodeSolidTilesInRange(SDL_FRect _rect);
    void renderAimDirection(SDL_FPoint start, float firingLength);
};

#endif