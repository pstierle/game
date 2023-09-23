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

    SDL_Surface *pineappleSurface = IMG_Load("textures/pineapple.png");
    textures[TextureType::PLAYER_PINEAPPLE] = SDL_CreateTextureFromSurface(state.renderer, pineappleSurface);
    SDL_FreeSurface(pineappleSurface);

    SDL_Surface *zombieSurface = IMG_Load("textures/zombie.png");
    textures[TextureType::PLAYER_ZOMBIE] = SDL_CreateTextureFromSurface(state.renderer, zombieSurface);
    SDL_FreeSurface(zombieSurface);

    SDL_Surface *frogSurface = IMG_Load("textures/frog.png");
    textures[TextureType::PLAYER_FROG] = SDL_CreateTextureFromSurface(state.renderer, frogSurface);
    SDL_FreeSurface(frogSurface);

    SDL_Surface *babyYodaSurface = IMG_Load("textures/baby_yoda.png");
    textures[TextureType::PLAYER_BABY_YODA] = SDL_CreateTextureFromSurface(state.renderer, babyYodaSurface);
    SDL_FreeSurface(babyYodaSurface);

    SDL_Surface *marioSurface = IMG_Load("textures/mario.png");
    textures[TextureType::PLAYER_MARIO] = SDL_CreateTextureFromSurface(state.renderer, marioSurface);
    SDL_FreeSurface(marioSurface);

    SDL_Surface *pickachuSurface = IMG_Load("textures/pickachu.png");
    textures[TextureType::PLAYER_PICKACHU] = SDL_CreateTextureFromSurface(state.renderer, pickachuSurface);
    SDL_FreeSurface(pickachuSurface);

    SDL_Surface *spongebobSurface = IMG_Load("textures/spongebob.png");
    textures[TextureType::PLAYER_SPONGEBOB] = SDL_CreateTextureFromSurface(state.renderer, spongebobSurface);
    SDL_FreeSurface(spongebobSurface);

    SDL_Surface *bombSurface = IMG_Load("textures/bomb.png");
    textures[TextureType::WEAPON_BOMB] = SDL_CreateTextureFromSurface(state.renderer, bombSurface);
    SDL_FreeSurface(bombSurface);

    SDL_Surface *grenadeSurface = IMG_Load("textures/grenade.png");
    textures[TextureType::WEAPON_GRENADE] = SDL_CreateTextureFromSurface(state.renderer, grenadeSurface);
    SDL_FreeSurface(grenadeSurface);

    SDL_Surface *bombTargetSurface = IMG_Load("textures/bomb_target.png");
    textures[TextureType::BOMB_TARGET] = SDL_CreateTextureFromSurface(state.renderer, bombTargetSurface);
    SDL_FreeSurface(bombTargetSurface);

    SDL_Surface *shotgunSurface = IMG_Load("textures/shotgun.png");
    textures[TextureType::WEAPON_SHOTGUN] = SDL_CreateTextureFromSurface(state.renderer, shotgunSurface);
    SDL_FreeSurface(shotgunSurface);

    SDL_Surface *shotgunBulletSurface = IMG_Load("textures/shotgun_bullet.png");
    textures[TextureType::SHOTGUN_BULLET] = SDL_CreateTextureFromSurface(state.renderer, shotgunBulletSurface);
    SDL_FreeSurface(shotgunBulletSurface);
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