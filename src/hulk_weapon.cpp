#include "global.hpp"

extern State state;

HulkWeapon::HulkWeapon(int _cost) : Weapon(_cost)
{
    fireingSprite = Sprite(TextureType::ROCK_ROUND, {0, 0}, 64, 64);
    fireingRotation = 0;
    throwingRock = false;
}

void HulkWeapon::render()
{
    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        if (throwingRock)
        {
            SDL_Rect spriteSource = {0, 0, 32, 32};
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
    }
    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        Player player = state.game.currentPlayer();
        renderAimDirection(player.positionCenter(), 200);
    }
}

void HulkWeapon::update()
{
    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        Player player = state.game.currentPlayer();
        updateLaunchAngle(player.positionCenter());
    }
    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        if (throwingRock)
        {
            if (Util::rectOutOfWindow(fireingSprite.positionRect()))
            {
                state.game.setWeaponSelection();
                state.game.nextTurn();
                return;
            }

            if (intersectsSolidTile(fireingSprite.positionRect()) || intersectsPlayer(fireingSprite.positionRect(), true))
            {
                int range = 80;

                for (int i = 0; i < 150; i++)
                {
                    state.game.map.createParticle(Util::rockDestroyParticle(fireingSprite.positionCenter(), range));
                }

                SDL_FRect impactRange = {fireingSprite.positionRect().x - range / 2, fireingSprite.positionRect().y - range / 2, static_cast<float>(fireingSprite.width + range), static_cast<float>(fireingSprite.height + range)};
                damagePlayersInRange(impactRange, 30, false);

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
        else
        {
            Player player = state.game.currentPlayer();
            SDL_FRect rockTargetRange = {player.position.x, player.positionCenter().y + player.height / 2, static_cast<float>(player.width), 20};
            interactWorldInRange(rockTargetRange);
            throwingRock = true;
        }
    }
}

void HulkWeapon::leftMouseUp()
{
    state.game.weaponMenu.specialWeapons[WeaponType::HULK].cost = 10000;
    Player player = state.game.currentPlayer();
    fireingSprite.position = {player.position.x, player.position.y - 32};
    throwStartTime = SDL_GetTicks();
    fireWeapon();
}
