#include "level/Grid.h"

Grid::Grid(sf::Vector2i tileSize) {
    this->tileSize = tileSize;
}

sf::Vector2i Grid::getTileSize() {
    return this->tileSize;
}
