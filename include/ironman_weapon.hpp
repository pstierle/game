#ifndef IRONMAN_WEAPON_HPP
#define IRONMAN_WEAPON_HPP

#include "global.hpp"

class IronmanWeapon : public Weapon
{
public:
    Sprite fireingSprite;

    float velocityX;
    float velocityY;
    float aimingSpriteRotation;
    bool drop;
    Uint16 launchStartTime;

    IronmanWeapon(int _cost);

    void render() override;
    void update() override;
    void leftMouseUp() override;
};

#endif