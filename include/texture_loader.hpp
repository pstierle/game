#ifndef TEXTURE_LOADER_HPP
#define TEXTURE_LOADER_HPP

#include "global.hpp"

class TextureLoader
{
public:
    std::map<TextureType, SDL_Texture *> textures;

    TextureLoader();

    void init();
    SDL_Texture *get(TextureType textureType);
};

#endif