#include "global.hpp"

extern State state;

Shotgun::Shotgun(int _cost) : Weapon(_cost)
{
    aimingSprite = Sprite(TextureType::WEAPON_SHOTGUN, {0, 0}, 32, 32);

    fireingSprites.resize(10, Sprite());

    for (size_t i = 0; i < fireingSprites.size(); ++i)
    {
        fireingSprites[i] = Sprite(TextureType::BULLET, {0, 0}, 10, 10);
    }
}

void Shotgun::render()
{
    SDL_FRect positionRect = aimingSprite.positionRect();
    SDL_Rect sourceRect = {0, 0, 16, 16};

    if (launchAngle >= -90.0f && launchAngle <= 90.0f)
    {
        positionRect.x += 10;
        SDL_RenderCopyExF(state.renderer, aimingSprite.texture, &sourceRect, &positionRect, launchAngle, NULL, SDL_FLIP_NONE);
    }
    else
    {
        positionRect.x -= 10;
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
    float xOffset = state.game.currentPlayer().width - 5 - aimingSprite.width;
    float yOffset = state.game.currentPlayer().height - 5 - aimingSprite.height;

    aimingSprite.position = {state.game.currentPlayer().position.x + (xOffset / 2), state.game.currentPlayer().position.y + (yOffset / 2)};

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
                intersectingPlayer->damagePlayer(10);
            }

            if (intersectsSolidTile(fireingSpritePosition) || Util::calculateDistance(state.game.currentPlayer().position, {fireingSpritePosition.x, fireingSpritePosition.y}) > 150)
            {
                remove = true;
            }
            else
            {
                float initialSpeed = 400.0f;
                float radians = launchAngle * (3.14159265359f / 180.0f);

                float initialVelocityX = initialSpeed * cos(radians);
                float initialVelocityY = initialSpeed * sin(radians);

                fireingSprites[i].position.x += initialVelocityX * state.deltaTime;
                fireingSprites[i].position.y += initialVelocityY * state.deltaTime;
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
    for (size_t i = 0; i < state.game.players.size(); ++i)
    {
        if (i == static_cast<size_t>(state.game.currentTurn))
        {
            // Calculate the initial positions of the bullets
            float xOffset = state.game.players[i].width / 2;
            float yOffset = state.game.players[i].height / 2;

            // Offset each bullet's position differently
            for (size_t j = 0; j < fireingSprites.size(); ++j)
            {
                float angleOffset = (j - fireingSprites.size() / 2) * 20.0f; // Adjust angle offset as needed
                float radians = (launchAngle + angleOffset) * (3.14159265359f / 180.0f);

                fireingSprites[j].position = {
                    state.game.players[i].position.x + xOffset * cos(radians) - yOffset * sin(radians),
                    state.game.players[i].position.y + xOffset * sin(radians) + yOffset * cos(radians)};
            }

            state.game.players[i].bounceBack(launchAngle);

            break;
        }
    }

    // Fire the weapon
    fireWeapon();
}
