#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "global.hpp"

class Particle
{

public:
    Uint32 startLife;
    SDL_FPoint position;
    float velX, velY;
    int lifeTime, width, height, r, g, b, a;

    Particle(SDL_FPoint _position, int _width, int _height, int _lifeTime, int _r, int _g, int _b, int _a);
    void update();
    void render();
};
#endif