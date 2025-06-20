#include <utility>

#include "level/Tile.h"

Tile::Tile(Sprite _sprite): sprite(std::move(_sprite)) {
}
