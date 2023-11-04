#ifndef TILE_HPP
#define TILE_HPP

#include "global.hpp"

class Tile : public Sprite
{
public:
    TileType tileType;
    Tile();
    Tile(TileType _tileType, TextureType _textureType, SDL_FPoint _position);
    void explodeTile();
    void collideWater();
};

#endif