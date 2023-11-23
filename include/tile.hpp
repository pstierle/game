#ifndef TILE_HPP
#define TILE_HPP

#include "global.hpp"

class Tile : public Sprite
{
public:
    TileType tileType;
    Tile();
    Tile(TileType _tileType, SDL_Texture *_texture, SDL_FPoint _position);
    void explodeTile();
    void collideWater();
};

#endif