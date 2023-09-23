#ifndef TEXT_HPP
#define TEXT_HPP

#include "global.hpp"

class Text
{
public:
    SDL_FPoint position;
    SDL_Color color;
    std::string text;
    int width;

    bool center;

    Text();
    Text(SDL_FPoint _position, std::string _text);
    Text(SDL_FPoint _position, std::string _text, SDL_Color _color);

    void render();
};

#endif