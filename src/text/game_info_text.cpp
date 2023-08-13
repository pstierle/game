
#include "game_info_text.hpp"
#include "constants.hpp"
#include "state.hpp"

extern State state;

GameInfoText::GameInfoText() : Text({0, 0, 20, 20}, "0")
{
    fpsTimer = SDL_GetTicks();
    frameCount = 0;
    fps = 0;
}

GameInfoText::~GameInfoText() {}

void GameInfoText::update()
{
    Uint32 currentTime = SDL_GetTicks();
    frameCount++;

    if (currentTime - fpsTimer >= 500)
    {
        fps = frameCount;
        frameCount = 0;
        fpsTimer = currentTime;
        std::string parsed = std::to_string(fps) + "      Score: " + std::to_string(state.waveCount) + "      Health: " + std::to_string(state.playerHealth);
        text = parsed;
        rect.w = text.length() * FONT_SIZE;
    }
}