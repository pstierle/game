#include "global.hpp"

extern State state;

Weapon::Weapon(int _cost)
{
    mousePosition = {-1, -1};
    cost = _cost;
}

void Weapon::mouseMove(int x, int y)
{
    mousePosition.x = x;
    mousePosition.y = y;
}

void Weapon::render()
{
}

void Weapon::update()
{
}

void Weapon::leftMouseUp()
{
}

void Weapon::renderAimDirection(SDL_FPoint start, float firingLength)
{
    SDL_FPoint direction = {static_cast<float>(mousePosition.x) - start.x, static_cast<float>(mousePosition.y) - start.y};

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0)
    {
        direction.x /= length;
        direction.y /= length;
        launchAngle = atan2(direction.y, direction.x) * (180.0f / 3.14159265359f);
    }

    SDL_FPoint endPoint = {start.x + direction.x * firingLength, start.y + direction.y * firingLength};

    SDL_SetRenderDrawColor(state.renderer, COLOR_RED.r, COLOR_RED.g, COLOR_RED.b, 255);
    SDL_RenderDrawLineF(state.renderer, start.x, start.y, endPoint.x, endPoint.y);
}

void Weapon::fireWeapon()
{
    for (size_t i = 0; i < state.game.players.size(); ++i)
    {
        if (i == static_cast<size_t>(state.game.currentTurn))
        {
            state.game.players[i].credits = state.game.players[i].credits - cost;
            break;
        }
    }
    state.game.gameState = GameStateType::WEAPON_FIRING;
}

bool Weapon::intersectsSolidTile(SDL_FRect _rect)
{
    bool hasIntersection = false;

    for (int i = 0; i < GRID_ROWS; ++i)
    {
        for (int j = 0; j < GRID_COLS; ++j)
        {
            if (state.game.map.tileGrid[i][j].textureType == TextureType::ROCK)
            {
                SDL_FRect rockRect = state.game.map.tileGrid[i][j].positionRect();

                if (SDL_HasIntersectionF(&_rect, &rockRect))
                {
                    hasIntersection = true;
                    break;
                }
            }
        }
        if (hasIntersection)
        {
            break;
        }
    }

    return hasIntersection;
}

void Weapon::damagePlayersInRange(SDL_FRect _rect, int damage)
{
    for (size_t i = 0; i < state.game.players.size(); ++i)
    {
        SDL_FRect playerRect = state.game.players[i].positionRect();

        if (SDL_HasIntersectionF(&playerRect, &_rect))
        {
            state.game.players[i].damagePlayer(damage);
        }
    }
}

void Weapon::explodeSolidTilesInRange(SDL_FRect _rect)
{
    for (int i = 0; i < GRID_ROWS; ++i)
    {
        for (int j = 0; j < GRID_COLS; ++j)
        {

            if (state.game.map.tileGrid[i][j].textureType == TextureType::ROCK)
            {
                SDL_FRect tileRect = state.game.map.tileGrid[i][j].positionRect();

                if (SDL_HasIntersectionF(&_rect, &tileRect))
                {
                    state.game.map.tileGrid[i][j].setTexture(TextureType::NONE);
                    SDL_FPoint destroyRockPosition = {state.game.map.tileGrid[i][j].position.x + state.game.map.tileGrid[i][j].width / 2, state.game.map.tileGrid[i][j].position.y + state.game.map.tileGrid[i][j].height / 2};

                    for (int i = 0; i < 10; i++)
                    {
                        state.game.map.createParticle(Util::rockDestroyParticle(destroyRockPosition));
                    }
                }
            }
        }
    }
}
