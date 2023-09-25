#include "global.hpp"

extern State state;

TextureLoader::TextureLoader() {}

void TextureLoader::init()
{
    SDL_Surface *backgroundSurface = IMG_Load("textures/background.png");
    textures[TextureType::BACKGROUND] = SDL_CreateTextureFromSurface(state.renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    SDL_Surface *rockSurface = IMG_Load("textures/rock.png");
    textures[TextureType::ROCK] = SDL_CreateTextureFromSurface(state.renderer, rockSurface);
    SDL_FreeSurface(rockSurface);

    SDL_Surface *waterSurface = IMG_Load("textures/water.png");
    textures[TextureType::WATER] = SDL_CreateTextureFromSurface(state.renderer, waterSurface);
    SDL_FreeSurface(waterSurface);

    SDL_Surface *supermanSurface = IMG_Load("textures/superman.png");
    textures[TextureType::PLAYER_SUPERMAN] = SDL_CreateTextureFromSurface(state.renderer, supermanSurface);
    SDL_FreeSurface(supermanSurface);

    SDL_Surface *hulkSurface = IMG_Load("textures/hulk.png");
    textures[TextureType::PLAYER_HULK] = SDL_CreateTextureFromSurface(state.renderer, hulkSurface);
    SDL_FreeSurface(hulkSurface);

    SDL_Surface *ironmanSurface = IMG_Load("textures/ironman.png");
    textures[TextureType::PLAYER_IRONMAN] = SDL_CreateTextureFromSurface(state.renderer, ironmanSurface);
    SDL_FreeSurface(ironmanSurface);

    SDL_Surface *airstrikeSurface = IMG_Load("textures/airstrike.png");
    textures[TextureType::WEAPON_AIRSTRIKE] = SDL_CreateTextureFromSurface(state.renderer, airstrikeSurface);
    SDL_FreeSurface(airstrikeSurface);

    SDL_Surface *grenadeSurface = IMG_Load("textures/grenade.png");
    textures[TextureType::WEAPON_GRENADE] = SDL_CreateTextureFromSurface(state.renderer, grenadeSurface);
    SDL_FreeSurface(grenadeSurface);

    SDL_Surface *airstrikeTargetSurface = IMG_Load("textures/airstrike_target.png");
    textures[TextureType::AIRSTRIKE_TARGET] = SDL_CreateTextureFromSurface(state.renderer, airstrikeTargetSurface);
    SDL_FreeSurface(airstrikeTargetSurface);

    SDL_Surface *shotgunSurface = IMG_Load("textures/shotgun.png");
    textures[TextureType::WEAPON_SHOTGUN] = SDL_CreateTextureFromSurface(state.renderer, shotgunSurface);
    SDL_FreeSurface(shotgunSurface);

    SDL_Surface *sniperSurface = IMG_Load("textures/sniper.png");
    textures[TextureType::WEAPON_SNIPER] = SDL_CreateTextureFromSurface(state.renderer, sniperSurface);
    SDL_FreeSurface(sniperSurface);

    SDL_Surface *weaponSupermanSurface = IMG_Load("textures/weapon_superman.png");
    textures[TextureType::WEAPON_SUPERMAN] = SDL_CreateTextureFromSurface(state.renderer, weaponSupermanSurface);
    SDL_FreeSurface(weaponSupermanSurface);

    SDL_Surface *weaponIronmanSurface = IMG_Load("textures/weapon_ironman.png");
    textures[TextureType::WEAPON_IRONMAN] = SDL_CreateTextureFromSurface(state.renderer, weaponIronmanSurface);
    SDL_FreeSurface(weaponIronmanSurface);

    SDL_Surface *weaponHulkSurface = IMG_Load("textures/weapon_hulk.png");
    textures[TextureType::WEAPON_HULK] = SDL_CreateTextureFromSurface(state.renderer, weaponHulkSurface);
    SDL_FreeSurface(weaponHulkSurface);

    SDL_Surface *bulletSurface = IMG_Load("textures/bullet.png");
    textures[TextureType::BULLET] = SDL_CreateTextureFromSurface(state.renderer, bulletSurface);
    SDL_FreeSurface(bulletSurface);
}

SDL_Texture *TextureLoader::get(TextureType textureType)
{
    auto it = textures.find(textureType);
    if (it != textures.end())
    {
        return it->second;
    }
    return nullptr;
}