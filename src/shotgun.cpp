#include "global.hpp"

extern State state;

Shotgun::Shotgun(int _cost) : Weapon(_cost)
{
    aimingSprite = Sprite(TextureType::WEAPON_SHOTGUN, {0, 0}, 32, 32);

    fireingSprites.resize(3, Sprite());

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
        SDL_RenderCopyExF(state.renderer, aimingSprite.texture, &sourceRect, &positionRect, launchAngle, NULL, SDL_FLIP_NONE);
    }
    else
    {
        SDL_RenderCopyExF(state.renderer, aimingSprite.texture, &sourceRect, &positionRect, launchAngle, NULL, SDL_FLIP_VERTICAL);
    }

    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        renderAimDirection(aimingSprite.positionCenter(), 150);
    }

    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        for (size_t i = 0; i < fireingSprites.size(); ++i)
        {
            if (ignoreSprite(i))
            {
                continue;
            }
            fireingSprites[i].render();
        }
    }
}

void Shotgun::update()
{
    aimingSprite.position = {state.game.currentPlayer().position.x + 10, state.game.currentPlayer().position.y + 10};

    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        updateLaunchAngle({aimingSprite.positionCenter().x, aimingSprite.positionCenter().y});
    }

    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        int windowWidth, windowHeight;
        SDL_GetWindowSize(state.window, &windowWidth, &windowHeight);

        for (size_t i = 0; i < fireingSprites.size(); ++i)
        {
            if (ignoreSprite(i))
            {
                continue;
            }

            if (fireingSprites[i].position.x <= 0 || fireingSprites[i].position.y <= 0 || fireingSprites[i].position.x + fireingSprites[i].width >= windowWidth || fireingSprites[i].position.y + fireingSprites[i].height >= windowHeight)
            {
                explodedSprites.push_back(i);
                continue;
            }

            SDL_FRect fireingSpritePosition = fireingSprites[i].positionRect();

            for (size_t i = 0; i < state.game.players.size(); ++i)
            {
                if (state.game.players[i].name == state.game.currentPlayer().name)
                {
                    continue;
                }

                SDL_FRect playerRect = state.game.players[i].positionRect();

                if (SDL_HasIntersectionF(&playerRect, &fireingSpritePosition))
                {
                    state.game.players[i].damagePlayer(2);
                }
            }

            if (intersectsSolidTile(fireingSpritePosition) || Util::calculateDistance(state.game.currentPlayer().position, {fireingSpritePosition.x, fireingSpritePosition.y}) > 150)
            {
                explodedSprites.push_back(i);
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
        }

        if (explodedSprites.size() == 3)
        {
            state.game.setWeaponSelection();
            state.game.nextTurn();
            return;
        }
    }
}

void Shotgun::leftMouseUp()
{
    fireingSprites[0].position = {aimingSprite.positionCenter().x, aimingSprite.positionCenter().y - 10};
    fireingSprites[1].position = {aimingSprite.positionCenter().x, aimingSprite.positionCenter().y};
    fireingSprites[2].position = {aimingSprite.positionCenter().x, aimingSprite.positionCenter().y + 10};

    for (size_t i = 0; i < state.game.players.size(); ++i)
    {
        if (i == static_cast<size_t>(state.game.currentTurn))
        {
            state.game.currentPlayer().bounceBack(launchAngle);
        }
    }

    fireWeapon();
}

bool Shotgun::ignoreSprite(size_t index)
{
    auto it = std::find(explodedSprites.begin(), explodedSprites.end(), index);
    return it != explodedSprites.end();
}
