#ifndef MAP_HPP
#define MAP_HPP

#include "global.hpp"

class Map
{
public:
    std::vector<std::vector<Sprite>> tileGrid;
    std::vector<std::vector<Sprite>> backGroundTileGrid;
    std::vector<Particle> particles;

    Map();
    void setup();
    void render();
    void update();
    void createParticle(Particle _particle);
};

#endif