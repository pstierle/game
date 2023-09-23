#ifndef MENU_WEAPON_HPP
#define MENU_WEAPON_HPP

#include "global.hpp"

class MenuWeapon : public Sprite
{
public:
    WeaponType type;
    std::string name;
    int cost;

    MenuWeapon();
    MenuWeapon(WeaponType _type, TextureType _textureType, SDL_FPoint _position, std::string _name, int _cost);
};

#endif