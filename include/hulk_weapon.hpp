#ifndef HULK_WEAPON_HPP
#define HULK_WEAPON_HPP

#include "global.hpp"

class HulkWeapon : public Weapon
{
public:
    Sprite fireingSprite;
    Uint16 throwStartTime;
    bool throwingRock;
    float fireingRotation;

    HulkWeapon(int _cost);

    void render() override;
    void update() override;
    void leftMouseUp() override;
};

#endif