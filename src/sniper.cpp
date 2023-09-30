#include "global.hpp"

extern State state;

Sniper::Sniper(int _cost) : Weapon(_cost)
{
    aimingSprite = Sprite(TextureType::WEAPON_SNIPER, {0, 0}, 32, 32);
    fireingSprite = Sprite(TextureType::BULLET, {0, 0}, 10, 10);
    aimingSprite.position = {state.game.currentPlayer().position.x + 10, state.game.currentPlayer().position.y + 10};
}

void Sniper::render()
{
    SDL_FRect positionRect = aimingSprite.positionRect();
    SDL_Rect sourceRect = {0, 0, 16, 16};

    if (launchAngle >= -90.0f && launchAngle <= 90.0f)
    {
        SDL_RenderCopyExF(state.renderer, aimingSprite.texture, &sourceRect, &positionRect, launchAngle, NULL, SDL_FLIP_NONE);
    }
    else
    {
        SDL_RenderCopyExF(state.renderer, aimingSprite.texture, &sourceRect, &positionRect, launchAngle, NULL, SDL_FLIP_VERTICAL);
    }

    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        renderAimDirection(aimingSprite.positionCenter(), 400);
    }

    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        fireingSprite.render();
    }
}

void Sniper::update()
{
    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        updateLaunchAngle(aimingSprite.positionCenter());
    }
    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        if (Util::rectOutOfWindow(fireingSprite.positionRect()) || intersectsPlayer(fireingSprite.positionRect(), true) || intersectsSolidTile(fireingSprite.positionRect()) || Util::calculateDistance(state.game.currentPlayer().positionCenter(), fireingSprite.positionCenter()) > 1000)
        {
            if (intersectsPlayer(fireingSprite.positionRect(), true))
            {
                damagePlayersInRange(fireingSprite.positionRect(), 20, true);
            }

            state.game.setWeaponSelection();
            state.game.nextTurn();
            return;
        }

        float speed = 1000.0f;
        float deltaTime = state.deltaTime;
        float radians = launchAngle * (3.14159265359f / 180.0f);

        float velocityX = speed * cos(radians);
        float velocityY = speed * sin(radians);

        fireingSprite.position.x += velocityX * deltaTime;
        fireingSprite.position.y += velocityY * deltaTime;
    }
}

void Sniper::leftMouseUp()
{
    Player player = state.game.currentPlayer();
    fireingSprite.position = {player.position.x, player.position.y};

    fireWeapon();
}
