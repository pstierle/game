#include "global.hpp"

extern State state;

TextureLoader::TextureLoader() {}

void TextureLoader::init()
{
    SDL_Surface *skySurface = IMG_Load("assets/textures/sky.png");
    textures[TextureType::SKY] = SDL_CreateTextureFromSurface(state.renderer, skySurface);
    SDL_FreeSurface(skySurface);

    SDL_Surface *skyLightSurface = IMG_Load("assets/textures/sky-light.png");
    textures[TextureType::SKY_LIGHT] = SDL_CreateTextureFromSurface(state.renderer, skyLightSurface);
    SDL_FreeSurface(skyLightSurface);

    SDL_Surface *rockSurface = IMG_Load("assets/textures/rock.png");
    textures[TextureType::ROCK] = SDL_CreateTextureFromSurface(state.renderer, rockSurface);
    SDL_FreeSurface(rockSurface);

    SDL_Surface *rockRoundSurface = IMG_Load("assets/textures/rock_round.png");
    textures[TextureType::ROCK_ROUND] = SDL_CreateTextureFromSurface(state.renderer, rockRoundSurface);
    SDL_FreeSurface(rockRoundSurface);

    SDL_Surface *waterSurface = IMG_Load("assets/textures/water.png");
    textures[TextureType::WATER] = SDL_CreateTextureFromSurface(state.renderer, waterSurface);
    SDL_FreeSurface(waterSurface);

    SDL_Surface *supermanSurface = IMG_Load("assets/textures/superman.png");
    textures[TextureType::PLAYER_SUPERMAN] = SDL_CreateTextureFromSurface(state.renderer, supermanSurface);
    SDL_FreeSurface(supermanSurface);

    SDL_Surface *hulkSurface = IMG_Load("assets/textures/hulk.png");
    textures[TextureType::PLAYER_HULK] = SDL_CreateTextureFromSurface(state.renderer, hulkSurface);
    SDL_FreeSurface(hulkSurface);

    SDL_Surface *ironmanSurface = IMG_Load("assets/textures/ironman.png");
    textures[TextureType::PLAYER_IRONMAN] = SDL_CreateTextureFromSurface(state.renderer, ironmanSurface);
    SDL_FreeSurface(ironmanSurface);

    SDL_Surface *airstrikeSurface = IMG_Load("assets/textures/airstrike.png");
    textures[TextureType::WEAPON_AIRSTRIKE] = SDL_CreateTextureFromSurface(state.renderer, airstrikeSurface);
    SDL_FreeSurface(airstrikeSurface);

    SDL_Surface *grenadeSurface = IMG_Load("assets/textures/grenade.png");
    textures[TextureType::WEAPON_GRENADE] = SDL_CreateTextureFromSurface(state.renderer, grenadeSurface);
    SDL_FreeSurface(grenadeSurface);

    SDL_Surface *airstrikeTargetSurface = IMG_Load("assets/textures/airstrike_target.png");
    textures[TextureType::AIRSTRIKE_TARGET] = SDL_CreateTextureFromSurface(state.renderer, airstrikeTargetSurface);
    SDL_FreeSurface(airstrikeTargetSurface);

    SDL_Surface *shotgunSurface = IMG_Load("assets/textures/shotgun.png");
    textures[TextureType::WEAPON_SHOTGUN] = SDL_CreateTextureFromSurface(state.renderer, shotgunSurface);
    SDL_FreeSurface(shotgunSurface);

    SDL_Surface *sniperSurface = IMG_Load("assets/textures/sniper.png");
    textures[TextureType::WEAPON_SNIPER] = SDL_CreateTextureFromSurface(state.renderer, sniperSurface);
    SDL_FreeSurface(sniperSurface);

    SDL_Surface *weaponSupermanSurface = IMG_Load("assets/textures/weapon_superman.png");
    textures[TextureType::WEAPON_SUPERMAN] = SDL_CreateTextureFromSurface(state.renderer, weaponSupermanSurface);
    SDL_FreeSurface(weaponSupermanSurface);

    SDL_Surface *weaponIronmanSurface = IMG_Load("assets/textures/weapon_ironman.png");
    textures[TextureType::WEAPON_IRONMAN] = SDL_CreateTextureFromSurface(state.renderer, weaponIronmanSurface);
    SDL_FreeSurface(weaponIronmanSurface);

    SDL_Surface *weaponHulkSurface = IMG_Load("assets/textures/weapon_hulk.png");
    textures[TextureType::WEAPON_HULK] = SDL_CreateTextureFromSurface(state.renderer, weaponHulkSurface);
    SDL_FreeSurface(weaponHulkSurface);

    SDL_Surface *bulletSurface = IMG_Load("assets/textures/bullet.png");
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