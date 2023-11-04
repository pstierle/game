#ifndef MAP_HPP
#define MAP_HPP

#include "global.hpp"

class Map
{
public:
    std::vector<std::vector<Tile>> tileGrid;
    std::vector<Particle> particles;

    Map();
    void setup();
    void render();
    void update();
    void loadMapInfo();
    void createParticle(Particle particle);
    TextureType textureTypeFromMapInfo(int identifier);
    TileType tileTypeFromTextureType(TextureType type);
};

#endif