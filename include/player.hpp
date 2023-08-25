#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include "sprite.hpp"
#include "item.hpp"

class Player : public Sprite
{
public:
    int health;
    int mouseX;
    int mouseY;
    float dx;
    float dy;
    std::vector<Item> inventory;

    Player();
    ~Player();

    void keyDown(int keyCode);
    void keyUp(int keyCode);
    void update();
    bool inRangeOfItem(Item item);
    void addToInventory(Item item);
};

#endif