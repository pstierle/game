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

        renderAimDirection(leftEyePosition, 550);
        renderAimDirection(rightEyePosition, 550);
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
    }
}

void SupermanWeapon::leftMouseUp()
{
    Player player = state.game.currentPlayer();
    fireWeapon();
}
