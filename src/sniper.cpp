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
        renderAimDirection(aimingSprite.center(), 400);
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
        updateLaunchAngle(aimingSprite.center());
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
            intersectingPlayer->damagePlayer(10);
            state.game.setWeaponSelection();
            state.game.nextTurn();
            return;
        }

        if (intersectsSolidTile(fireingSpritePosition) || Util::calculateDistance(state.game.currentPlayer().position, {fireingSpritePosition.x, fireingSpritePosition.y}) > 1900)
        {
            state.game.setWeaponSelection();
            state.game.nextTurn();
            return;
        }
        else
        {
            float speed = 1000.0f;
            float deltaTime = state.deltaTime;
            float radians = launchAngle * (3.14159265359f / 180.0f);

            float velocityX = speed * cos(radians);
            float velocityY = speed * sin(radians);

            fireingSprite.position.x += velocityX * deltaTime;
            fireingSprite.position.y += velocityY * deltaTime;
        }
    }
}

void Sniper::leftMouseUp()
{
    Player player = state.game.currentPlayer();
    fireingSprite.position = {player.position.x, player.position.y};

    fireWeapon();
}
