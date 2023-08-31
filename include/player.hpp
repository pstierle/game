#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include "sprite.hpp"
#include "item.hpp"
#include "direction.hpp"

class Player : public Sprite
{
public:
    int health;
    int mouseX;
    int mouseY;
    int selectedItemIndex;
    SDL_Point currentDirection;
    SDL_Point lastDirection;
    std::vector<Item> inventory;
    std::vector<Sprite> inventorySlots;
    Direction direction;
    Uint32 animationStartTime;
    SDL_Point animationSprite;

    Player();
    ~Player();

    void keyDown(int keyCode);
    void keyUp(int keyCode);
    void update();
    bool inRangeOfItem(Item item);
    void addToInventory(Item item);
    void renderInventory();
    void selectItem(int index);
    void updatePlayerSprite();
    void updatePlayerPosition();
    void handleAttack();
};

#endif