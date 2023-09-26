#include "global.hpp"

extern State state;

Grenade::Grenade(int _cost) : Weapon(_cost)
{
    fireingSprite = Sprite(TextureType::WEAPON_GRENADE, {0, 0}, 22, 22);
    throwStartTime = 0;
    velocityX = 0;
    velocityY = 0;
}

void Grenade::render()
{
    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        fireingSprite.render();
    }
    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        renderAimDirection(100, 0);
    }
}

void Grenade::update()
{
    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        int windowWidth, windowHeight;
        SDL_GetWindowSize(state.window, &windowWidth, &windowHeight);

        if (fireingSprite.position.x <= 0 || fireingSprite.position.y <= 0 || fireingSprite.position.x + fireingSprite.width >= windowWidth || fireingSprite.position.y + fireingSprite.height >= windowHeight)
        {
            state.game.setWeaponSelection();
            state.game.nextTurn();
            return;
        }

        SDL_FRect grenadeRect = {fireingSprite.position.x, fireingSprite.position.y, static_cast<float>(fireingSprite.width), static_cast<float>(fireingSprite.height)};

        if (intersectsSolidTile(grenadeRect))
        {
            SDL_FPoint impactPosition = {fireingSprite.position.x + fireingSprite.height / 2, fireingSprite.position.y + fireingSprite.width / 2};

            for (int i = 0; i < 150; i++)
            {
                state.game.map.createParticle(Util::bombExplosionParticle(impactPosition));
            }

            SDL_FRect impactRange = {impactPosition.x - 50, impactPosition.y - 50, 100, 100};

            damagePlayersInRange(impactRange, 10);
            explodeSolidTilesInRange(impactRange);

            state.game.setWeaponSelection();
            state.game.nextTurn();
        }
        else
        {
            float speed = 400.0f;

            float radians = launchAngle * (3.14159265359f / 180.0f);
            float elapsed = static_cast<float>(SDL_GetTicks() - throwStartTime) / 2000.0f;

            float initialVelocityX = cos(radians);
            float initialVelocityY = sin(radians);

            if (false)
            {

                fireingSprite.position.x += initialVelocityX * speed * state.deltaTime;
                fireingSprite.position.y += initialVelocityY * speed * state.deltaTime;
            }
            else
            {
                fireingSprite.position.x += speed * initialVelocityX * state.deltaTime;
                fireingSprite.position.y += speed * (initialVelocityY * elapsed) * elapsed * state.deltaTime * -1;
            }
        }
    }
}

void Grenade::leftMouseUp()
{
    Player player = state.game.currentPlayer();
    fireingSprite.position = {player.position.x, player.position.y};

    float radians = launchAngle * (3.14159265359f / 180.0f);
    velocityX = cos(radians);
    velocityY = sin(radians);

    throwStartTime = SDL_GetTicks();
    fireWeapon();
}