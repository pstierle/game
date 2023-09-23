#include "global.hpp"

extern State state;

Bomb::Bomb(int _cost) : Weapon(_cost)
{
    aimingSprite = Sprite(TextureType::BOMB_TARGET, {0, 0}, 64, 64);
    fireingSprite = Sprite(TextureType::WEAPON_BOMB, {0, 0}, 32, 32);
}

void Bomb::render()
{
    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        fireingSprite.render();
    }
    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        aimingSprite.render();
    }
}

void Bomb::update()
{
    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        int windowWidth, windowHeight;
        SDL_GetWindowSize(state.window, &windowWidth, &windowHeight);

        if (fireingSprite.position.y >= windowHeight)
        {
            state.game.setWeaponSelection();
            state.game.nextTurn();
            return;
        }

        SDL_FRect bombRect = {fireingSprite.position.x, fireingSprite.position.y, static_cast<float>(fireingSprite.width), static_cast<float>(fireingSprite.height)};

        if (intersectsSolidTile(bombRect))
        {
            SDL_FPoint impactPosition = {fireingSprite.position.x + fireingSprite.height / 2, fireingSprite.position.y + fireingSprite.width / 2};

            for (int i = 0; i < 150; i++)
            {
                state.game.map.createParticle(Util::bombExplosionParticle(impactPosition));
            }

            SDL_FRect impactRange = {impactPosition.x - 50, impactPosition.y - 50, 100, 100};

            damagePlayersInRange(impactRange, 20);
            explodeSolidTilesInRange(impactRange);

            state.game.setWeaponSelection();
            state.game.nextTurn();
        }
        else
        {
            fireingSprite.position.y += 1 * GRAVITY * state.deltaTime;
        }
    }
    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        aimingSprite.position = {static_cast<float>(mousePosition.x) - 32, static_cast<float>(mousePosition.y) - 32};
    }
}

void Bomb::leftMouseUp()
{
    fireingSprite.position.x = mousePosition.x - 32;
    fireingSprite.position.y = 0;
    fireWeapon();
}
