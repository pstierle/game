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
        renderAimDirection(leftEyePosition(), fireingLength);
        renderAimDirection(rightEyePosition(), fireingLength);
    }
    if (state.game.gameState == GameStateType::WEAPON_SELECTED)
    {
        renderAimDirection(leftEyePosition(), 3000);
        renderAimDirection(rightEyePosition(), 3000);
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

        SDL_FPoint leftEyeHit = Util::endpointFromLine(leftEyePosition(), launchAngle * (3.14159265359f / 180.0f), fireingLength);
        SDL_FPoint rightEyeHit = Util::endpointFromLine(rightEyePosition(), launchAngle * (3.14159265359f / 180.0f), fireingLength);

        if (Util::pointOutOfWindow(leftEyeHit) && Util::pointOutOfWindow(rightEyeHit))
        {
            state.game.setWeaponSelection();
            state.game.nextTurn();
            return;
        }

        SDL_FRect impactRect = {leftEyeHit.x, leftEyeHit.y, 6, 6};

        explodeSolidTilesInRange(impactRect);

        damagePlayersInRange({leftEyeHit.x, leftEyeHit.y, 1, 1}, 1, true);
        damagePlayersInRange({rightEyeHit.x, rightEyeHit.y, 1, 1}, 1, true);
    }
}

void SupermanWeapon::leftMouseUp()
{
    state.game.weaponMenu.specialWeapons[WeaponType::SUPERMAN].cost = 10000;
    Player player = state.game.currentPlayer();
    fireWeapon();
}

SDL_FPoint SupermanWeapon::leftEyePosition()
{
    return {state.game.currentPlayer().positionCenter().x - 7, state.game.currentPlayer().positionCenter().y - 6};
}

SDL_FPoint SupermanWeapon::rightEyePosition()
{
    return {state.game.currentPlayer().positionCenter().x - 1, state.game.currentPlayer().positionCenter().y - 6};
}