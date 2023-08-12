
#include "fps_text.hpp"
#include <iostream>

FPSText::FPSText() : Text({0, 0, 100, 100}, "111")
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

        std::cout << "FPS: " << fps << std::endl;
    }
}