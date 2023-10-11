#include "global.hpp"

extern State state;

Grenade::Grenade(int _cost) : Weapon(_cost)
{
    fireingSprite = Sprite(TextureType::WEAPON_GRENADE, {0, 0}, 22, 22);
    throwStartTime = 0;
    fireingRotation = 0;
}

void Grenade::render()
{
    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        SDL_Rect spriteSource = {0, 0, 16, 16};
        SDL_FRect positionDestination = fireingSprite.positionRect();

        if (launchAngle >= -90.0f && launchAngle <= 90.0f)
        {
            SDL_RenderCopyExF(state.renderer, fireingSprite.texture, &spriteSource, &positionDestination, fireingRotation, nullptr, SDL_FLIP_NONE);
        }
        else
        {
            SDL_RenderCopyExF(state.renderer, fireingSprite.texture, &spriteSource, &positionDestination, fireingRotation * -1, nullptr, SDL_FLIP_NONE);
        }
    }
    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        renderAimDirection(state.game.currentPlayer().positionCenter(), 150);
    }
}

void Grenade::update()
{
    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        Player player = state.game.currentPlayer();
        updateLaunchAngle({player.position.x, player.position.y});
    }

    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        if (Util::rectOutOfWindow(fireingSprite.positionRect()))
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
            interactWorldInRange(impactRange);

            state.game.setWeaponSelection();
            state.game.nextTurn();
            return;
        }

        float speed = 400.0f;

        float radians = launchAngle * (3.14159265359f / 180.0f);
        float elapsed = static_cast<float>(SDL_GetTicks() - throwStartTime) / 2000.0f;

        float velocityX = cos(radians);
        float velocityY = sin(radians) + elapsed;

        fireingSprite.position.x += velocityX * speed * state.deltaTime;
        fireingSprite.position.y += velocityY * speed * state.deltaTime;

        fireingRotation += 300 * state.deltaTime;
    }
}

void Grenade::leftMouseUp()
{
    Player player = state.game.currentPlayer();
    fireingSprite.position = {player.position.x, player.position.y};
    throwStartTime = SDL_GetTicks();
    fireWeapon();
}