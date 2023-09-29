#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "global.hpp"

class Particle : Entity
{

public:
    Uint32 startLife;
    float velX, velY;
    int lifeTime, r, g, b, a;

    Particle(SDL_FPoint _position, int _width, int _height, int _lifeTime, int _r, int _g, int _b, int _a);
    void update() override;
    void render() override;
};
#endif