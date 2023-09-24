#ifndef SNIPER_HPP
#define SNIPER_HPP

#include "global.hpp"

class Sniper : public Weapon
{
public:
    Sprite aimingSprite;
    Sprite fireingSprite;

    Sniper(int _cost);

    void render() override;
    void update() override;
    void leftMouseUp() override;
};

#endif