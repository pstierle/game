#ifndef BOMB_HPP
#define BOMB_HPP

#include "global.hpp"

class Bomb : public Weapon
{
public:
    Sprite aimingSprite;
    Sprite fireingSprite;

    Bomb(int _cost);

    void render() override;
    void update() override;
    void leftMouseUp() override;
};

#endif