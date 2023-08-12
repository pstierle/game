#ifndef FPS_TEXT_HPP
#define FPS_TEXT_HPP

#include "text.hpp"

class FPSText : public Text
{
public:
    FPSText();
    void update();

private:
    Uint32 fpsTimer;
    Uint32 frameCount;
    Uint32 fps;
};

#endif