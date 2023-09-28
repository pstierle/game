#include "global.hpp"

extern State state;

SupermanWeapon::SupermanWeapon(int _cost) : Weapon(_cost)
{
}

void SupermanWeapon::render()
{
    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
    }
    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        SDL_FPoint leftEyePosition = {state.game.currentPlayer().center().x - 7, state.game.currentPlayer().center().y - 6};
        SDL_FPoint rightEyePosition = {state.game.currentPlayer().center().x - 1, state.game.currentPlayer().center().y - 6};

        renderAimDirection(leftEyePosition, 5000);
        renderAimDirection(rightEyePosition, 5000);
    }
}

void SupermanWeapon::update()
{
    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        Player player = state.game.currentPlayer();
        updateLaunchAngle({player.position.x, player.position.y});
    }
    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        SDL_FPoint leftEyePosition = {state.game.currentPlayer().center().x - 7, state.game.currentPlayer().center().y - 6};

        SDL_FPoint direction = {static_cast<float>(mousePosition.x) - leftEyePosition.x, static_cast<float>(mousePosition.y) - leftEyePosition.y};

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > 0)
        {
            direction.x /= length;
            direction.y /= length;
        }

        SDL_FPoint endPoint = {leftEyePosition.x + direction.x * 5000, leftEyePosition.y + direction.y * 5000};

        for (int i = 0; i < GRID_ROWS; ++i)
        {
            for (int j = 0; j < GRID_COLS; ++j)
            {
                if (state.game.map.tileGrid[i][j].textureType == TextureType::ROCK)
                {
                    SDL_FRect rockRect = state.game.map.tileGrid[i][j].positionRect();

                    if (Util::lineIntersectsRect(leftEyePosition, endPoint, rockRect))
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

        for (size_t i = 0; i < state.game.players.size(); ++i)
        {
            SDL_FRect playerRect = state.game.players[i].positionRect();

            if (Util::lineIntersectsRect(leftEyePosition, endPoint, playerRect))
            {
                state.game.players[i].damagePlayer(20);
            }
        }

        state.game.setWeaponSelection();
        state.game.nextTurn();
        return;
    }
}

void SupermanWeapon::leftMouseUp()
{
    state.game.weaponMenu.specialWeapons[WeaponType::SUPERMAN].cost = 10000;
    Player player = state.game.currentPlayer();
    fireWeapon();
}
