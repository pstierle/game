#ifndef SWORD_HPP
#define SWORD_HPP

#include <SDL2/SDL.h>
#include "item.hpp"

class Sword : public Item
{
public:
    Sword(SDL_FPoint _position);
};

#endif