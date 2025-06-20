#ifndef TILE_H
#define TILE_H
#include "SFML/Graphics/Sprite.hpp"

using namespace sf;

class Tile {
public:
    Tile(Sprite sprite);

    Sprite* getSprite() {
        return &sprite;
    }

private:
    Sprite sprite;
};

#endif //TILE_H
