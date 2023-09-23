#include "global.hpp"

extern State state;

Text::Text()
{
}

Text::Text(SDL_FPoint _position, std::string _text)
{
    position = _position;
    color = {255,
             255,
             255,
             255};

    text = _text;
    center = false;
    width = 0;
}

Text::Text(SDL_FPoint _position, std::string _text, SDL_Color _color)
{
    position = _position;
    text = _text;
    color = _color;
    center = false;
    width = 0;
}

void Text::render()
{
    SDL_SetRenderDrawBlendMode(state.renderer, SDL_BLENDMODE_BLEND);
    SDL_Surface *textSurface = TTF_RenderText_Blended(state.font, text.c_str(), color);
    SDL_FRect destination = {position.x, position.y, static_cast<float>(textSurface->w), static_cast<float>(textSurface->h)};
    width = textSurface->w;

    if (center)
    {
        destination.x = destination.x - destination.w / 2;
    }

    if (textSurface)
    {
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(state.renderer, textSurface);

        if (textTexture)
        {
            SDL_RenderCopyF(state.renderer, textTexture, nullptr, &destination);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}
