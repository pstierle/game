#ifndef SUPERMAN_WEAPON_HPP
#define SUPERMAN_WEAPON_HPP

#include "global.hpp"

class SupermanWeapon : public Weapon
{
public:
    int fireingLength;

    SupermanWeapon(int _cost);

    void render() override;
    void update() override;
    void leftMouseUp() override;
    SDL_FPoint leftEyePosition();
    SDL_FPoint rightEyePosition();
};

#endif