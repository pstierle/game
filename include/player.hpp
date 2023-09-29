#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "global.hpp"

class Player : public Entity
{
public:
    SDL_Texture *texture;
    TextureType textureType;
    Text nameText, healthText;
    std::string name;
    SDL_Color color;
    Uint32 bounceStart;
    WeaponType specialWeaponType;

    int xVelocity, yVelocity, credits, health, launchAngle;

    Player();
    Player(TextureType _textureType, std::string _name, SDL_FPoint _position, SDL_Color _color, int _width, int _height, WeaponType _specialWeaponType);

    void update() override;
    void updatePosition();
    void updateInfoText();

    void render() override;
    void renderModel();
    void renderInfoText();

    void damagePlayer(int damage);
    void bounceBack(float launchAngle);
};

#endif