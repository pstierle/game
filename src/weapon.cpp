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

void Weapon::updateLaunchAngle(SDL_FPoint start)
{
    SDL_FPoint direction = {static_cast<float>(mousePosition.x) - start.x, static_cast<float>(mousePosition.y) - start.y};
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0)
    {
        direction.x /= length;
        direction.y /= length;
        launchAngle = atan2(direction.y, direction.x) * (180.0f / 3.14159265359f);
    }
}

void Weapon::renderAimDirection(SDL_FPoint start, float firingLength)
{
    float angleInRadians = launchAngle * (3.14159265359f / 180.0f);
    Util::drawLine(start, COLOR_RED, angleInRadians, firingLength);
}

void Weapon::fireWeapon()
{
    for (size_t i = 0; i < state.game.players.size(); ++i)
    {
        if (state.game.players[i].name == state.game.currentPlayer().name)
        {
            state.game.players[i].credits = state.game.players[i].credits - cost;
            break;
        }
    }
    state.game.gameState = GameStateType::WEAPON_FIRING;
}

bool Weapon::intersectsSolidTile(SDL_FRect rect)
{
    bool hasIntersection = false;

    for (int i = 0; i < GRID_ROWS; ++i)
    {
        for (int j = 0; j < GRID_COLS; ++j)
        {
            if (state.game.map.tileGrid[i][j].tileType == TileType::SOLID)
            {
                SDL_FRect rockRect = state.game.map.tileGrid[i][j].positionRect();

                if (SDL_HasIntersectionF(&rect, &rockRect))
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

bool Weapon::intersectsPlayer(SDL_FRect rect, bool ignoreCurrentPlayer)
{
    bool hasIntersection = false;

    for (size_t i = 0; i < state.game.players.size(); ++i)
    {
        if (ignoreCurrentPlayer && state.game.players[i].name == state.game.currentPlayer().name)
        {
            continue;
        }

        SDL_FRect playerRect = state.game.players[i].positionRect();
        if (SDL_HasIntersectionF(&rect, &playerRect))
        {
            hasIntersection = true;
            break;
        }
    }

    return hasIntersection;
}

void Weapon::damagePlayersInRange(SDL_FRect rect, int damage, bool ignoreCurrentPlayer)
{
    for (size_t i = 0; i < state.game.players.size(); ++i)
    {
        if (ignoreCurrentPlayer && state.game.players[i].name == state.game.currentPlayer().name)
        {
            continue;
        }

        SDL_FRect playerRect = state.game.players[i].positionRect();

        if (SDL_HasIntersectionF(&playerRect, &rect))
        {
            state.game.players[i].damagePlayer(damage);
        }
    }
}

void Weapon::interactWorldInRange(SDL_FRect rect)
{
    for (int i = 0; i < GRID_ROWS; ++i)
    {
        for (int j = 0; j < GRID_COLS; ++j)
        {

            SDL_FRect tileRect = state.game.map.tileGrid[i][j].positionRect();

            if (state.game.map.tileGrid[i][j].tileType == TileType::SOLID)
            {
                if (SDL_HasIntersectionF(&rect, &tileRect))
                {
                    state.game.map.tileGrid[i][j].explodeTile();
                }
            }

            if (state.game.map.tileGrid[i][j].tileType == TileType::WATER)
            {

                if (SDL_HasIntersectionF(&rect, &tileRect))
                {
                    state.game.map.tileGrid[i][j].collideWater();
                }
            }
        }
    }
}
