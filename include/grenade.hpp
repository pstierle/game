#ifndef GRENADE_HPP
#define GRENADE_HPP

#include "global.hpp"

class Grenade : public Weapon
{
public:
    Sprite fireingSprite;

    float velocityX;
    float velocityY;
    Uint16 throwStartTime;

    Grenade(int _cost);

    void render() override;
    void update() override;
    void leftMouseUp() override;
};

#endif