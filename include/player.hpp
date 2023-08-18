#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "sprite.hpp"

class Player : public Sprite
{
public:
    int health;
    int mouseX;
    int mouseY;

    Player();
    ~Player();

    void update();
};

#endif