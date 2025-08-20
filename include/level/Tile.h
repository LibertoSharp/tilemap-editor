#ifndef TILE_H
#define TILE_H
#include <string>

#include "TileInfo.h"
#include "SFML/Graphics/Sprite.hpp"

using namespace sf;

class Tile {
public:
    Tile(IntRect r, std::string atlasID);

    Sprite* getSprite() {
        return &sprite;
    }

    void setInfo(TileInfo info) {
        this->info = info;
    }

    std::string getAtlasID() {
        return atlasID;
    }

    IntRect getRect() {
        return rect;
    }



private:
    Sprite sprite;
    std::string atlasID;
    IntRect rect;
    TileInfo info;
};

#endif //TILE_H
