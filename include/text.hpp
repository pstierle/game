#ifndef TEXT_HPP
#define TEXT_HPP

#include "global.hpp"

class Text
{
public:
    SDL_FPoint position;
    SDL_Color color;
    std::string text;
    int textWidth, textHeight;
    TTF_Font *font;

    bool center;

    Text();
    Text(SDL_FPoint _position, std::string _text, bool _large);
    Text(SDL_FPoint _position, std::string _text, SDL_Color _color, bool _large);

    void render();
};

#endif