#include "global.hpp"

extern State state;

WeaponMenu::WeaponMenu()
{
    menuWeapons.resize(3, MenuWeapon());
    menuWeapons[0] = MenuWeapon(WeaponType::BOMB, TextureType::WEAPON_BOMB, {0, 0}, "Bomb", 20);
    menuWeapons[1] = MenuWeapon(WeaponType::GRENADE, TextureType::WEAPON_GRENADE, {0, 0}, "Grenade", 20);
    menuWeapons[2] = MenuWeapon(WeaponType::SHOTGUN, TextureType::WEAPON_SHOTGUN, {0, 0}, "Shotgun", 20);

    for (size_t i = 0; i < menuWeapons.size(); i++)
    {
        menuWeapons[i].position = {i * 45.0f + 20.0f, 20.0f};
    }

    playerInfoText = Text({20.0f, 60.0f}, "");

    hoveredIndex = -1;
}

void WeaponMenu::render()
{
    // render background
    SDL_SetRenderDrawColor(state.renderer, COLOR_GREY.r, COLOR_GREY.g, COLOR_GREY.b, 255);
    SDL_FRect backGroundRect = {10, 10, menuWeapons.size() * 40.0f + playerInfoText.width, 80.0f};
    SDL_RenderFillRectF(state.renderer, &backGroundRect);

    // render weapons
    for (size_t i = 0; i < menuWeapons.size(); i++)
    {
        Player player = state.game.currentPlayer();
        SDL_FRect outlineRect = {menuWeapons[i].position.x, menuWeapons[i].position.y, 32, 32};

        SDL_SetRenderDrawColor(state.renderer, 122, 122, 122, 255);
        SDL_RenderFillRectF(state.renderer, &outlineRect);

        if (hoveredIndex == static_cast<int>(i) && menuWeapons[i].cost <= player.credits)
        {
            SDL_SetRenderDrawColor(state.renderer, COLOR_RED.r, COLOR_RED.g, COLOR_RED.b, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(state.renderer, COLOR_DARK_GREY.r, COLOR_DARK_GREY.g, COLOR_DARK_GREY.b, 255);
        }

        SDL_RenderDrawRectF(state.renderer, &outlineRect);

        menuWeapons[i].render();

        if (menuWeapons[i].cost > player.credits)
        {
            SDL_SetRenderDrawColor(state.renderer, COLOR_RED.r, COLOR_RED.g, COLOR_RED.b, 255);
            SDL_RenderDrawLineF(state.renderer, outlineRect.x, outlineRect.y, outlineRect.x + outlineRect.w, outlineRect.y + outlineRect.h);
            SDL_RenderDrawLineF(state.renderer, outlineRect.x, outlineRect.y + outlineRect.h, outlineRect.x + outlineRect.w, outlineRect.y);
        }
    }

    // render player info
    playerInfoText.render();
}

void WeaponMenu::update()
{
    Player player = state.game.currentPlayer();

    // update player info
    playerInfoText.text = player.name + ", Credits: " + std::to_string(player.credits);
}

void WeaponMenu::mouseMove(int x, int y)
{
    hoveredIndex = -1;

    for (size_t i = 0; i < menuWeapons.size(); i++)
    {
        SDL_FRect outlineRect = {menuWeapons[i].position.x, menuWeapons[i].position.y, 32, 32};

        if (Util::pointInRect({static_cast<float>(x), static_cast<float>(y)}, outlineRect))
        {
            hoveredIndex = i;
        }
    }
}

void WeaponMenu::mouseClick()
{
    if (hoveredIndex != -1)
    {
        Player player = state.game.currentPlayer();
        MenuWeapon targetWeapon = menuWeapons[hoveredIndex];

        if (targetWeapon.cost < player.credits)
        {
            if (targetWeapon.type == WeaponType::BOMB)
            {
                state.game.selectedWeapon = new Bomb(targetWeapon.cost);
                state.game.gameState = GameStateType::WEAPON_SELECTED;
                hoveredIndex = -1;
            }
            if (targetWeapon.type == WeaponType::GRENADE)
            {
                state.game.selectedWeapon = new Grenade(targetWeapon.cost);
                state.game.gameState = GameStateType::WEAPON_SELECTED;
                hoveredIndex = -1;
            }
            if (targetWeapon.type == WeaponType::SHOTGUN)
            {
                state.game.selectedWeapon = new Shotgun(targetWeapon.cost);
                state.game.gameState = GameStateType::WEAPON_SELECTED;
                hoveredIndex = -1;
            }
        }
    }
}