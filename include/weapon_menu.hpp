#ifndef WEAPON_MENU_HPP
#define WEAPON_MENU_HPP

#include "global.hpp"

class WeaponMenu
{
public:
    std::map<WeaponType, MenuWeapon> specialWeapons;
    std::vector<MenuWeapon> menuWeapons;
    Text playerInfoText;
    int hoveredIndex;

    WeaponMenu();
    void render();
    void renderMenuWeapon(MenuWeapon _weapon, bool hovered);
    void update();
    void mouseMove(int x, int y);
    void mouseClick();

    MenuWeapon specialWeapon(WeaponType _type);
};

#endif