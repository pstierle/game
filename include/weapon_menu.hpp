#ifndef WEAPON_MENU_HPP
#define WEAPON_MENU_HPP

#include "global.hpp"

class WeaponMenu
{
public:
    std::vector<MenuWeapon> menuWeapons;
    Text playerInfoText;
    int hoveredIndex;

    WeaponMenu();
    void render();
    void update();
    void mouseMove(int x, int y);
    void mouseClick();
};

#endif