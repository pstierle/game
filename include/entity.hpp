#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "global.hpp"

class Entity
{

public:
    SDL_FPoint position;
    int width, height;

    Entity();
    Entity(SDL_FPoint _position, int _width, int _height);
    virtual void update();
    virtual void render();
    SDL_FRect positionRect();
    SDL_FPoint positionCenter();
};
#endif