#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "sprite.hpp"

class Player : public Sprite
{
public:
    int health;
    int mouseX;
    int mouseY;
    float dx;
    float dy;

    Player();
    ~Player();

    void updateDirection(int keyCode);
    void resetDirection(int keyCode);
    void update();
};

#endif