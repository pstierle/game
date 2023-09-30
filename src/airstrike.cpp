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

        if (intersectsSolidTile(fireingSprite.positionRect()) || intersectsPlayer(fireingSprite.positionRect(), true))
        {
            int range = 50;

            for (int i = 0; i < 100; i++)
            {
                state.game.map.createParticle(Util::bombExplosionParticle(fireingSprite.positionCenter(), range));
            }

            SDL_FRect impactRange = {fireingSprite.positionRect().x - range / 2, fireingSprite.positionRect().y - range / 2, static_cast<float>(fireingSprite.width + range), static_cast<float>(fireingSprite.height + range)};
            damagePlayersInRange(impactRange, 10, false);
            explodeSolidTilesInRange(impactRange);

            state.game.setWeaponSelection();
            state.game.nextTurn();
            return;
        }

        float speed = 500.0f;
        fireingSprite.position.y += 1 * state.deltaTime * speed;
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
