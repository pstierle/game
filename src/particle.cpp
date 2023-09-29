#include "global.hpp"

extern State state;

Particle::Particle(SDL_FPoint _position, int _width, int _height, int _lifeTime, int _r, int _g, int _b, int _a) : Entity(_position, _width, _height)
{
    startLife = SDL_GetTicks();
    lifeTime = _lifeTime;
    r = _r;
    g = _g;
    b = _b;
    a = _a;
}

void Particle::update()
{
    int speed = 50;
    int angle = std::rand() % (100 - 80 + 1) + 80;

    velX = speed * cos(angle);
    velY = speed * sin(angle);

    position.x += velX * state.deltaTime;
    position.y += velY * state.deltaTime;
}

void Particle::render()
{
    SDL_FRect positionDestination = {position.x, position.y, static_cast<float>(width), static_cast<float>(height)};
    SDL_SetRenderDrawColor(state.renderer, r, g, b, a);
    SDL_RenderFillRectF(state.renderer, &positionDestination);
}