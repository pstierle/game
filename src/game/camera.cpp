#include "camera.hpp"
#include "state.hpp"
#include <iostream>

extern State state;

Camera::Camera()
{
}

void Camera::updatePosition(SDL_FRect _position)
{
    position = _position;
}

void Camera::update()
{
    int windowWidth, windowHeight;
    SDL_GetWindowSize(state.window, &windowWidth, &windowHeight);

    position.x = state.player.position.x - windowWidth / 2;
    position.y = state.player.position.y - windowHeight / 2;

    if (position.x < 0)
    {
        position.x = 0;
    }
    if (position.y < 0)
    {
        position.y = 0;
    }
    if (position.x >= windowWidth / 2)
    {
        position.x = windowWidth / 2;
    }
    if (position.y > position.h)
    {
        position.y = position.h;
    }
}