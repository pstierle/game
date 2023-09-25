#ifndef AIRSTRIKE_HPP
#define AIRSTRIKE_HPP

#include "global.hpp"

class Airstrike : public Weapon
{
public:
    Sprite aimingSprite;
    Sprite fireingSprite;

    Airstrike(int _cost);

    void render() override;
    void update() override;
    void leftMouseUp() override;
};

#endif