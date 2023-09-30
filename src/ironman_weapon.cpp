#include "global.hpp"

extern State state;

IronmanWeapon::IronmanWeapon(int _cost) : Weapon(_cost)
{
    fireingSprite = Sprite(TextureType::WEAPON_AIRSTRIKE, {0, 0}, 22, 22);
    aimingSpriteRotation = 0;
    drop = false;
}

void IronmanWeapon::render()
{
    if (state.game.gameState == GameStateType::WEAPON_FIRING)
    {
        SDL_Rect spriteSource = {0, 0, 16, 16};
        SDL_FRect positionDestination = fireingSprite.positionRect();

        // Render the sprite with rotation
        SDL_RenderCopyExF(state.renderer, fireingSprite.texture, &spriteSource, &positionDestination, aimingSpriteRotation - 90, NULL, SDL_FLIP_NONE);
    }
}

void IronmanWeapon::update()
{
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

        SDL_FRect grenadeRect = {fireingSprite.position.x, fireingSprite.position.y, static_cast<float>(fireingSprite.width), static_cast<float>(fireingSprite.height)};

        if (intersectsSolidTile(grenadeRect))
        {
            SDL_FPoint impactPosition = {fireingSprite.position.x + fireingSprite.height / 2, fireingSprite.position.y + fireingSprite.width / 2};

            for (int i = 0; i < 150; i++)
            {
                state.game.map.createParticle(Util::bombExplosionParticle(impactPosition));
            }

            SDL_FRect impactRange = {impactPosition.x - 50, impactPosition.y - 50, 100, 100};

            damagePlayersInRange(impactRange, 20, false);
            explodeSolidTilesInRange(impactRange);

            state.game.setWeaponSelection();
            state.game.nextTurn();
        }
        else
        {
            float speed = 400.0f;

            if (drop)
            {
                fireingSprite.position.y += speed * state.deltaTime;
            }
            else
            {
                if (SDL_GetTicks() - launchStartTime <= 500)
                {
                    fireingSprite.position.y -= speed * state.deltaTime;
                    aimingSpriteRotation = 0;
                }
                else
                {
                    int mouseX = mousePosition.x;
                    int mouseY = mousePosition.y;

                    float directionX = static_cast<float>(mouseX) - fireingSprite.position.x;
                    float directionY = static_cast<float>(mouseY) - fireingSprite.position.y;

                    float length = sqrt(directionX * directionX + directionY * directionY);

                    if (length != 0)
                    {
                        directionX /= length;
                        directionY /= length;
                    }

                    fireingSprite.position.x += directionX * speed * state.deltaTime;
                    fireingSprite.position.y += directionY * speed * state.deltaTime;

                    float angle = atan2(directionY, directionX) * (180.0f / M_PI);

                    aimingSpriteRotation = angle;

                    if (Util::calculateDistance({fireingSprite.position.x, fireingSprite.position.y}, {static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)}) <= 5)
                    {
                        drop = true;
                        aimingSpriteRotation = 90;
                    }
                }
            }
        }
    }
}

void IronmanWeapon::leftMouseUp()
{
    state.game.weaponMenu.specialWeapons[WeaponType::IRONMAN].cost = 10000;
    Player player = state.game.currentPlayer();
    fireingSprite.position = {player.position.x + player.width / 2, player.position.y};
    launchStartTime = SDL_GetTicks();
    fireWeapon();
}
