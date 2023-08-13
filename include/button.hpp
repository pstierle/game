#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include "text.hpp"

class Button
{
public:
    Text labelText;
    SDL_FRect position;
    Button(SDL_FRect _position, std::string _label);
    ~Button();
    Button();

    void render();
    bool isClicked(int mouseX, int mouseY);
};

#endif