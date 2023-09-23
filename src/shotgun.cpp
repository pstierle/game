#include "global.hpp"

extern State state;

Shotgun::Shotgun(int _cost) : Weapon(_cost)
{
    aimingSprite = Sprite(TextureType::WEAPON_SHOTGUN, {0, 0}, 32, 32);
    fireingSprite = Sprite(TextureType::SHOTGUN_BULLET, {0, 0}, 10, 10);
}

void Shotgun::render()
{
    SDL_FRect positionRect = aimingSprite.positionRect();
    SDL_Rect sourceRect = {0, 0, 16, 16};

    if (launchAngle >= 90 || launchAngle <= -90)
    {
        SDL_RenderCopyExF(state.renderer, aimingSprite.texture, &sourceRect, &positionRect, launchAngle, NULL, SDL_FLIP_VERTICAL);
    }
    else
    {
        SDL_RenderCopyExF(state.renderer, aimingSprite.texture, &sourceRect, &positionRect, launchAngle, NULL, SDL_FLIP_NONE);
    }

    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        fireingSprite.render();
    }
}

void Shotgun::update()
{
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

        if (launchAngle >= 90 || launchAngle <= -90)
        {
            aimingSprite.position = {player.position.x, player.position.y};
        }
        else
        {
            aimingSprite.position = {player.position.x + 16, player.position.y};
        }
        std::cout << launchAngle << std::endl;
        //  + launchAngle * 0.2f
    }
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

        SDL_FRect fireingSpritePosition = fireingSprite.positionRect();

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
            state.game.setWeaponSelection();
            state.game.nextTurn();
            return;
        }

        if (intersectsSolidTile(fireingSpritePosition))
        {
            state.game.setWeaponSelection();
            state.game.nextTurn();
            return;
        }

        float initialSpeed = 500.0f;
        float deltaTime = state.deltaTime;
        float gravity = 400.0f;

        float radians = launchAngle * (3.14159265359f / 180.0f);

        float initialVelocityX = initialSpeed * cos(radians);
        float initialVelocityY = initialSpeed * sin(radians);

        fireingSprite.position.x += initialVelocityX * deltaTime;
        fireingSprite.position.y += initialVelocityY * deltaTime - 0.5f * gravity * deltaTime * deltaTime;
        initialVelocityY += gravity * deltaTime;
    }

    //         state.game.setWeaponSelection();
    //         state.game.nextTurn();
}

void Shotgun::leftMouseUp()
{
    Player player = state.game.currentPlayer();
    fireingSprite.position = {player.position.x, player.position.y};
    fireWeapon();
}
