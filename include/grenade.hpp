#ifndef GRENADE_HPP
#define GRENADE_HPP

#include "global.hpp"

class Grenade : public Weapon
{
public:
    Sprite fireingSprite;
    Uint16 throwStartTime;

    float fireingRotation;

    Grenade(int _cost);

    void render() override;
    void update() override;
    void leftMouseUp() override;
};

#endif