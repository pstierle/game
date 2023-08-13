
#include "fps_text.hpp"
#include "constants.hpp"

FPSText::FPSText() : Text({10, 10, FONT_SIZE, FONT_SIZE}, "0")
{
    fpsTimer = SDL_GetTicks();
    frameCount = 0;
    fps = 0;
}

void FPSText::update()
{
    Uint32 currentTime = SDL_GetTicks();
    frameCount++;

    if (currentTime - fpsTimer >= 500)
    {
        fps = frameCount;
        frameCount = 0;
        fpsTimer = currentTime;

        text = std::to_string(fps);
        rect.w = text.length() * FONT_SIZE;
    }
}