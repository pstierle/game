#include "global.hpp"

extern State state;

SupermanWeapon::SupermanWeapon(int _cost) : Weapon(_cost)
{
    fireingLength = 0;
}

void SupermanWeapon::render()
{
    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        SDL_FPoint leftEyePosition = {state.game.currentPlayer().positionCenter().x - 7, state.game.currentPlayer().positionCenter().y - 6};
        SDL_FPoint rightEyePosition = {state.game.currentPlayer().positionCenter().x - 1, state.game.currentPlayer().positionCenter().y - 6};

        renderAimDirection(leftEyePosition, fireingLength);
        renderAimDirection(rightEyePosition, fireingLength);
    }
    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        SDL_FPoint leftEyePosition = {state.game.currentPlayer().positionCenter().x - 7, state.game.currentPlayer().positionCenter().y - 6};
        SDL_FPoint rightEyePosition = {state.game.currentPlayer().positionCenter().x - 1, state.game.currentPlayer().positionCenter().y - 6};

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
        fireingLength = fireingLength + 5;

        SDL_FPoint leftEyePosition = {state.game.currentPlayer().positionCenter().x - 7, state.game.currentPlayer().positionCenter().y - 6};
        SDL_FPoint rightEyePosition = {state.game.currentPlayer().positionCenter().x - 1, state.game.currentPlayer().positionCenter().y - 6};

        SDL_FPoint leftEyeHit = Util::endpointFromLine(leftEyePosition, launchAngle * (3.14159265359f / 180.0f), fireingLength);
        SDL_FPoint rightEyeHit = Util::endpointFromLine(rightEyePosition, launchAngle * (3.14159265359f / 180.0f), fireingLength);

        if (Util::pointOutOfWindow(leftEyeHit) && Util::pointOutOfWindow(rightEyeHit))
        {
            state.game.setWeaponSelection();
            state.game.nextTurn();
            return;
        }

        for (int i = 0; i < GRID_ROWS; ++i)
        {
            for (int j = 0; j < GRID_COLS; ++j)
            {
                if (state.game.map.tileGrid[i][j].textureType == TextureType::ROCK)
                {
                    SDL_FRect rockRect = state.game.map.tileGrid[i][j].positionRect();

                    if (Util::pointInRect(leftEyeHit, rockRect) || Util::pointInRect(rightEyeHit, rockRect))
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
            if (i == static_cast<size_t>(state.game.currentTurn))
            {
                continue;
            }
            SDL_FRect playerRect = state.game.players[i].positionRect();

            if (Util::pointInRect(leftEyeHit, playerRect) || Util::pointInRect(rightEyeHit, playerRect))
            {
                state.game.players[i].damagePlayer(2);
            }
        }
    }
}

void SupermanWeapon::leftMouseUp()
{
    state.game.weaponMenu.specialWeapons[WeaponType::SUPERMAN].cost = 10000;
    Player player = state.game.currentPlayer();
    fireWeapon();
}
