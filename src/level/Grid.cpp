#include "level/Grid.h"

Grid::Grid(unsigned _tileSize, sf::Vector2i _gridSize) : tileSize(_tileSize), gridSize(_gridSize) {
    this->tilemap = new std::optional<Tile>[gridSize.x * gridSize.y];
}

unsigned Grid::getTileSize() const {
    return this->tileSize;
}

sf::Vector2i Grid::getGridSize() const {
    return this->gridSize;
}

void Grid::setTile(int x, int y, Tile tile) {
    tile.getSprite()->setPosition(Vector2f(x*tileSize, y*tileSize));
    tilemap[(tileSize*x+y)] = tile;
}

void Grid::setTile(sf::Vector2i pos, Tile tile) {
    setTile(pos.x, pos.y, tile);
}

void Grid::setTileInfo(int x, int y, TileInfo tile) {
    tilemap[(tileSize*x+y)]->setInfo(tile);
}

void Grid::setTileInfo(sf::Vector2i pos, TileInfo tile) {
    setTileInfo(pos.x, pos.y, tile);
}

std::optional<Tile>* Grid::operator[](int index) const {
    return &tilemap[index];
}
