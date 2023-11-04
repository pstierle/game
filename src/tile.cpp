#include "global.hpp"

extern State state;

Tile::Tile() : Sprite()
{
}

Tile::Tile(TileType _tileType, TextureType _textureType, SDL_FPoint _position) : Sprite(_textureType, _position, 32, 32)
{
    tileType = _tileType;
}

void Tile::explodeTile()
{
    Tile::setTexture(TextureType::SKY);
    Tile::tileType = TileType::NON_SOLID;

    for (int i = 0; i < 10; i++)
    {
        state.game.map.createParticle(Util::rockDestroyParticle(Tile::positionCenter(), 10));
    }
}

void Tile::collideWater()
{
    for (int i = 0; i < 10; i++)
    {
        state.game.map.createParticle(Util::waterCollisionParticle(Tile::positionCenter(), 10));
    }
}
