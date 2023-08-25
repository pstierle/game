#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SDL2/SDL.h>

class Camera
{
public:
    SDL_FRect position;
    Camera();
    void updatePosition(SDL_FRect _position);
    void update();
};

#endif