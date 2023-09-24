#include "global.hpp"

extern State state;

Shotgun::Shotgun(int _cost) : Weapon(_cost)
{
    aimingSprite = Sprite(TextureType::WEAPON_SHOTGUN, {0, 0}, 32, 32);
    fireingSprites.resize(3, Sprite());
    fireingSprites[0] = Sprite(TextureType::BULLET, {0, 0}, 10, 10);
    fireingSprites[1] = Sprite(TextureType::BULLET, {0, 0}, 10, 10);
    fireingSprites[2] = Sprite(TextureType::BULLET, {0, 0}, 10, 10);
    aimingSprite.position = {state.game.currentPlayer().position.x, state.game.currentPlayer().position.y};
}

void Shotgun::render()
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
        renderAimDirection(150, 0);
    }

    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        for (size_t i = 0; i < fireingSprites.size(); ++i)
        {
            fireingSprites[i].render();
        }
    }
}

void Shotgun::update()
{
    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        int windowWidth, windowHeight;
        SDL_GetWindowSize(state.window, &windowWidth, &windowHeight);

        std::vector<size_t> bulletsToRemove;

        for (size_t i = 0; i < fireingSprites.size(); ++i)
        {
            bool remove = false;

            if (fireingSprites[i].position.x <= 0 || fireingSprites[i].position.y <= 0 || fireingSprites[i].position.x + fireingSprites[i].width >= windowWidth || fireingSprites[i].position.y + fireingSprites[i].height >= windowHeight)
            {
                remove = true;
                continue;
            }

            SDL_FRect fireingSpritePosition = fireingSprites[i].positionRect();

            Player *intersectingPlayer = nullptr;

            for (size_t i = 0; i < state.game.players.size(); ++i)
            {
                if (state.game.players[i].name == state.game.currentPlayer().name)
                {
                    continue;
                }

                SDL_FRect playerRect = state.game.players[i].positionRect();

                if (SDL_HasIntersectionF(&playerRect, &fireingSpritePosition))
                {
                    intersectingPlayer = &state.game.players[i];
                }
            }

            if (intersectingPlayer != nullptr)
            {
                intersectingPlayer->health -= 10;
            }

            if (intersectsSolidTile(fireingSpritePosition) || Util::calculateDistance(state.game.currentPlayer().position, {fireingSpritePosition.x, fireingSpritePosition.y}) > 150)
            {
                remove = true;
            }
            else
            {
                float initialSpeed = 400.0f;
                float deltaTime = state.deltaTime;
                float gravity = 400.0f;
                float launchAngleOffset = launchAngle + (i * 5);
                float radians = launchAngleOffset * (3.14159265359f / 180.0f);

                float initialVelocityX = initialSpeed * cos(radians);
                float initialVelocityY = initialSpeed * sin(radians);

                fireingSprites[i].position.x += initialVelocityX * deltaTime;
                fireingSprites[i].position.y += initialVelocityY * deltaTime - 0.5f * gravity * deltaTime * deltaTime;
                initialVelocityY += gravity * deltaTime;
            }

            if (remove)
            {
                bulletsToRemove.push_back(i);
            }
        }

        for (int i = bulletsToRemove.size() - 1; i >= 0; --i)
        {
            fireingSprites.erase(fireingSprites.begin() + bulletsToRemove[i]);
        }

        if (fireingSprites.size() == 0)
        {
            state.game.setWeaponSelection();
            state.game.nextTurn();
            return;
        }
    }
}

void Shotgun::leftMouseUp()
{
    Player player = state.game.currentPlayer();

    for (size_t i = 0; i < fireingSprites.size(); ++i)
    {
        fireingSprites[i].position = {player.position.x, player.position.y};
    }

    fireWeapon();
}
