#include "button.hpp"
#include "util.hpp"
#include "text.hpp"
#include "constants.hpp"
#include "state.hpp"

extern State state;

Button::Button()
{
}

Button::~Button()
{
}

Button::Button(SDL_FRect _position, std::string _label)
{
    position = _position;
    labelText = Text(position, _label);
}

void Button::render()
{
    SDL_SetRenderDrawColor(state.renderer, 255, 0, 0, 255);
    SDL_RenderFillRectF(state.renderer, &position);
    labelText.render();
}

bool Button::isClicked(int mouseX, int mouseY)
{
    return Util::pointInRect(mouseX, mouseY, position);
}