#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "sprite.hpp"
#include <vector>

class Monster : public Sprite
{
public:
    double speed;
    std::vector<SDL_Point> visited;
    Monster(SDL_FPoint _position, SDL_Point _spritePosition);
    void update();
    SDL_Point currentGridPosition();
    bool validGridPosition(int x, int y, int rows, int cols);
    bool isEndPosition();
};

#endif