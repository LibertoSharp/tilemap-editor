#ifndef TILE_H
#define TILE_H
#include "TileInfo.h"
#include "SFML/Graphics/Sprite.hpp"

using namespace sf;

class Tile {
public:
    Tile(Sprite sprite);

    Sprite* getSprite() {
        return &sprite;
    }

    void setInfo(TileInfo info) {
        this->info = info;
    }



private:
    Sprite sprite;
    TileInfo info;
};

#endif //TILE_H
