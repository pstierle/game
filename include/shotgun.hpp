#ifndef SHOTGUN_HPP
#define SHOTGUN_HPP

#include "global.hpp"

class Shotgun : public Weapon
{
public:
    Sprite aimingSprite;
    std::vector<Sprite> fireingSprites;

    Shotgun(int _cost);

    void render() override;
    void update() override;
    void leftMouseUp() override;
};

#endif