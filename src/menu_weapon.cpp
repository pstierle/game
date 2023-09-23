#include "global.hpp"

MenuWeapon::MenuWeapon() : Sprite()
{
}

MenuWeapon::MenuWeapon(WeaponType _type, TextureType _textureType, SDL_FPoint _position, std::string _name, int _cost) : Sprite(_textureType, _position, 32, 32)
{
    name = _name;
    cost = _cost;
    type = _type;
}
