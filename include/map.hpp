#ifndef MAP_HPP
#define MAP_HPP

#include "global.hpp"

class Map
{
public:
    std::vector<std::vector<Sprite>> tileGrid;
    std::vector<Particle> particles;

    Map();
    void setup();
    void render();
    void update();
    void loadMapInfo();
    void createParticle(Particle particle);
    TextureType textureTypeFromMapInfo(int identifier);
};

#endif