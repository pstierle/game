#include "text.hpp"
#include "state.hpp"

extern State state;

Text::Text()
{
}

Text::Text(SDL_FRect _rect, std::string _text)
{
    rect = _rect;
    color = {255,
             255,
             255,
             255};

    text = _text;
}

Text::Text(SDL_FRect _rect, std::string _text, SDL_Color _color)
{
    rect = _rect;
    text = _text;
    color = _color;
}

void Text::render()
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(state.font, text.c_str(), color);

    if (textSurface)
    {
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(state.renderer, textSurface);
        if (textTexture)
        {
            SDL_RenderCopyF(state.renderer, textTexture, nullptr, &rect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}
