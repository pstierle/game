#include "global.hpp"

extern State state;

WeaponMenu::WeaponMenu()
{
    menuWeapons.resize(5, MenuWeapon());

    // reserve first slot for special weapon
    menuWeapons[0] = MenuWeapon();
    menuWeapons[1] = MenuWeapon(WeaponType::AIRSTRIKE, TextureType::WEAPON_AIRSTRIKE, {0, 0}, "Airstrike", 20);
    menuWeapons[2] = MenuWeapon(WeaponType::GRENADE, TextureType::WEAPON_GRENADE, {0, 0}, "Grenade", 20);
    menuWeapons[3] = MenuWeapon(WeaponType::SHOTGUN, TextureType::WEAPON_SHOTGUN, {0, 0}, "Shotgun", 20);
    menuWeapons[4] = MenuWeapon(WeaponType::SNIPER, TextureType::WEAPON_SNIPER, {0, 0}, "Sniper", 20);

    specialWeapons[WeaponType::SUPERMAN] = MenuWeapon(WeaponType::SUPERMAN, TextureType::WEAPON_SUPERMAN, {0, 0}, "Laser", 0);
    specialWeapons[WeaponType::IRONMAN] = MenuWeapon(WeaponType::IRONMAN, TextureType::WEAPON_IRONMAN, {0, 0}, "Rockets", 0);
    specialWeapons[WeaponType::HULK] = MenuWeapon(WeaponType::HULK, TextureType::WEAPON_HULK, {0, 0}, "Smash", 0);

    playerInfoText = Text({20.0f, 60.0f}, "", false);

    hoveredIndex = -1;
}

void WeaponMenu::render()
{
    Player player = state.game.currentPlayer();

    // background
    SDL_FRect backGroundRect = {10, 10, menuWeapons.size() * 47.0f, 75.0f};
    Util::drawRectangle(backGroundRect, COLOR_GREY, player.color, 2);

    // render weapons
    for (size_t i = 0; i < menuWeapons.size(); i++)
    {
        renderMenuWeapon(menuWeapons[i], hoveredIndex == static_cast<int>(i));
    }

    // render player info
    playerInfoText.render();
}

void WeaponMenu::renderMenuWeapon(MenuWeapon _weapon, bool hovered)
{
    Player player = state.game.currentPlayer();

    SDL_FRect menuWeaponRect = {_weapon.position.x, _weapon.position.y, static_cast<float>(_weapon.width), static_cast<float>(_weapon.height)};

    if (hovered && _weapon.cost <= player.credits)
    {
        Util::drawRectangle(menuWeaponRect, COLOR_LIGHT_GREY, COLOR_RED, 2);
    }
    else
    {
        Util::drawRectangle(menuWeaponRect, COLOR_LIGHT_GREY, COLOR_DARK_GREY, 2);
    }

    _weapon.render();

    if (_weapon.cost > player.credits)
    {
        SDL_SetRenderDrawColor(state.renderer, COLOR_RED.r, COLOR_RED.g, COLOR_RED.b, 255);
        SDL_RenderDrawLineF(state.renderer, menuWeaponRect.x, menuWeaponRect.y, menuWeaponRect.x + menuWeaponRect.w, menuWeaponRect.y + menuWeaponRect.h);
        SDL_RenderDrawLineF(state.renderer, menuWeaponRect.x, menuWeaponRect.y + menuWeaponRect.h, menuWeaponRect.x + menuWeaponRect.w, menuWeaponRect.y);
    }
}

void WeaponMenu::update()
{
    Player player = state.game.currentPlayer();
    menuWeapons[0] = specialWeapon(player.specialWeaponType);

    for (size_t i = 0; i < menuWeapons.size(); i++)
    {
        menuWeapons[i].position = {i * 45.0f + 20.0f, 20.0f};
    }

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

        if (targetWeapon.cost <= player.credits)
        {
            if (targetWeapon.type == WeaponType::AIRSTRIKE)
            {
                state.game.selectedWeapon = new Airstrike(targetWeapon.cost);
                state.game.gameState = GameStateType::WEAPON_SELECTED;
            }
            if (targetWeapon.type == WeaponType::GRENADE)
            {
                state.game.selectedWeapon = new Grenade(targetWeapon.cost);
                state.game.gameState = GameStateType::WEAPON_SELECTED;
            }
            if (targetWeapon.type == WeaponType::SHOTGUN)
            {
                state.game.selectedWeapon = new Shotgun(targetWeapon.cost);
                state.game.gameState = GameStateType::WEAPON_SELECTED;
            }
            if (targetWeapon.type == WeaponType::SNIPER)
            {
                state.game.selectedWeapon = new Sniper(targetWeapon.cost);
                state.game.gameState = GameStateType::WEAPON_SELECTED;
            }
            if (targetWeapon.type == WeaponType::IRONMAN)
            {
                state.game.selectedWeapon = new IronmanWeapon(targetWeapon.cost);
                state.game.gameState = GameStateType::WEAPON_SELECTED;
            }
            if (targetWeapon.type == WeaponType::SUPERMAN)
            {
                state.game.selectedWeapon = new SupermanWeapon(targetWeapon.cost);
                state.game.gameState = GameStateType::WEAPON_SELECTED;
            }
            if (targetWeapon.type == WeaponType::HULK)
            {
                state.game.selectedWeapon = new HulkWeapon(targetWeapon.cost);
                state.game.gameState = GameStateType::WEAPON_SELECTED;
            }
            hoveredIndex = -1;
        }
    }
}

MenuWeapon WeaponMenu::specialWeapon(WeaponType _type)
{
    auto it = specialWeapons.find(_type);
    if (it != specialWeapons.end())
    {
        return it->second;
    }

    return MenuWeapon();
}
