#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL.h>
#include <string>

class Text
{
public:
    SDL_FRect rect;
    SDL_Color color;
    std::string text;

    Text();
    Text(SDL_FRect _rect, std::string _text);
    Text(SDL_FRect _rect, std::string _text, SDL_Color _color);

    void render();
};

#endif