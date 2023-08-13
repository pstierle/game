#ifndef GAME_INFO_TEXT_HPP
#define GAME_INFO_TEXT_HPP

#include "text.hpp"

class GameInfoText : public Text
{
public:
    GameInfoText();
    ~GameInfoText();
    void update();

private:
    Uint32 fpsTimer;
    Uint32 frameCount;
    Uint32 fps;
};

#endif