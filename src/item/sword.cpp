#include "sword.hpp"
#include "item_type.hpp"

Sword::Sword(SDL_FPoint _position) : Item(_position, {2, 1}, 32, 32, 48, 48, ItemType::SWORD)
{
}
