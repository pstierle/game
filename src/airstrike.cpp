#include "global.hpp"

extern State state;

Airstrike::Airstrike(int _cost) : Weapon(_cost)
{
    aimingSprite = Sprite(TextureType::AIRSTRIKE_TARGET, {0, 0}, 64, 64);
    fireingSprite = Sprite(TextureType::WEAPON_AIRSTRIKE, {0, 0}, 32, 32);
}

void Airstrike::render()
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

void Airstrike::update()
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

        SDL_FRect AirstrikeRect = {fireingSprite.position.x, fireingSprite.position.y, static_cast<float>(fireingSprite.width), static_cast<float>(fireingSprite.height)};

        if (intersectsSolidTile(AirstrikeRect))
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
            float speed = 500.0f;
            fireingSprite.position.y += 1 * state.deltaTime * speed;
        }
    }
    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        aimingSprite.position = {static_cast<float>(mousePosition.x) - aimingSprite.width / 2, static_cast<float>(mousePosition.y) - aimingSprite.height / 2};
    }
}

void Airstrike::leftMouseUp()
{
    fireingSprite.position.x = mousePosition.x - aimingSprite.width / 2;
    fireingSprite.position.y = 0;
    fireWeapon();
}
