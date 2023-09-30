#include "global.hpp"

extern State state;

Text::Text()
{
}

Text::Text(SDL_FPoint _position, std::string _text, bool _large)
{
    position = _position;
    color = {255,
             255,
             255,
             255};

    text = _text;
    center = false;
    textWidth = 0;
    if (_large)
    {
        font = state.fontLarge;
    }
    else
    {
        font = state.font;
    }
}

Text::Text(SDL_FPoint _position, std::string _text, SDL_Color _color, bool _large)
{
    position = _position;
    text = _text;
    color = _color;
    center = false;
    textWidth = 0;
    if (_large)
    {
        font = state.fontLarge;
    }
    else
    {
        font = state.font;
    }
}

void Text::render()
{
    SDL_SetRenderDrawBlendMode(state.renderer, SDL_BLENDMODE_BLEND);
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_FRect destination = {position.x, position.y, static_cast<float>(textSurface->w), static_cast<float>(textSurface->h)};
    textWidth = textSurface->w;
    textHeight = textSurface->h;

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
