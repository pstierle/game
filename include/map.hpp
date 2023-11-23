#ifndef MAP_HPP
#define MAP_HPP

#include "global.hpp"

class Map
{
public:
    std::vector<std::vector<Tile>> tileGrid;
    std::vector<Particle> particles;

    Map();
    bool setup();
    void render();
    void update();
    void createParticle(Particle particle);
    TileType tileTypeFromName(std::string name);
};

#endif