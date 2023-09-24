#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "global.hpp"

class Player
{
public:
    SDL_FPoint position;
    SDL_Texture *texture;
    TextureType textureType;
    Text nameText;
    Text healthText;
    std::string name;
    SDL_Color color;
    int dx;
    int dy;
    int credits;
    int health;

    Player();
    Player(TextureType _textureType, std::string _name, SDL_FPoint _position, SDL_Color _color);

    void update();
    void updatePosition();
    void updateInfoText();

    void render();
    void renderModel();
    void renderInfoText();

    SDL_FRect positionRect();
};

#endif