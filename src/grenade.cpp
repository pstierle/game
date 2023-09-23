#include "global.hpp"

extern State state;

Grenade::Grenade(int _cost) : Weapon(_cost)
{
    fireingSprite = Sprite(TextureType::WEAPON_GRENADE, {0, 0}, 22, 22);
}

void Grenade::render()
{
    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        fireingSprite.render();
    }
    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        Player player = state.game.currentPlayer();
        SDL_FPoint playerPosition = {player.position.x + 16, player.position.y + 16};

        SDL_FPoint direction = {static_cast<float>(mousePosition.x) - playerPosition.x, static_cast<float>(mousePosition.y) - playerPosition.y};

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > 0)
        {
            direction.x /= length;
            direction.y /= length;
            launchAngle = atan2(direction.y, direction.x) * (180.0f / 3.14159265359f);
        }

        SDL_FPoint endPoint = {playerPosition.x + direction.x * 120.0f, playerPosition.y + direction.y * 120.0f};

        SDL_SetRenderDrawColor(state.renderer, COLOR_RED.r, COLOR_RED.g, COLOR_RED.b, 255);
        SDL_RenderDrawLineF(state.renderer, playerPosition.x, playerPosition.y, endPoint.x, endPoint.y);
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

        float initialSpeed = 400.0f;
        float deltaTime = state.deltaTime;
        float gravity = 400.0f;

        float radians = launchAngle * (3.14159265359f / 180.0f);

        float initialVelocityX = initialSpeed * cos(radians);
        float initialVelocityY = initialSpeed * sin(radians);

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
            fireingSprite.position.x += initialVelocityX * deltaTime;
            fireingSprite.position.y += initialVelocityY * deltaTime - 0.5f * gravity * deltaTime * deltaTime;
            initialVelocityY += gravity * deltaTime;
        }
    }
}

void Grenade::leftMouseUp()
{
    Player player = state.game.currentPlayer();
    fireingSprite.position = {player.position.x, player.position.y};
    fireWeapon();
}
