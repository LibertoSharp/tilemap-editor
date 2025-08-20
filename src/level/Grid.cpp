#include "level/Grid.h"

#include <iostream>

Grid::Grid(unsigned _tileSize, sf::Vector2i _gridSize) : tileSize(_tileSize), gridSize(_gridSize) {
    this->tilemap.resize(gridSize.x * gridSize.y);
}

unsigned Grid::getTileSize() const {
    return this->tileSize;
}

sf::Vector2i Grid::getGridSize() const {
    return this->gridSize;
}

void Grid::setTile(int x, int y, std::optional<Tile> tile) {
    if (x < 0 || x >= gridSize.x || y < 0 || y >= gridSize.y) return;

    if (tile.has_value()) {
        tile.value().getSprite()->setPosition(Vector2f(x*tileSize, y*tileSize));
        tilesets.insert(tile.value().getAtlasID());
    }

    tilemap[(gridSize.x*y+x)] = tile;
}

void Grid::setTile(sf::Vector2i pos, std::optional<Tile> tile) {
    setTile(pos.x, pos.y, tile);
}

void Grid::setTileInfo(int x, int y, TileInfo tile) {
    tilemap[(gridSize.x*y+x)]->setInfo(tile);
}

void Grid::setTileInfo(sf::Vector2i pos, TileInfo tile) {
    setTileInfo(pos.x, pos.y, tile);
}

std::set<std::string> Grid::getTileset() {
    return tilesets;
}

std::optional<Tile> Grid::getTile(int x, int y) {
    return tilemap[(gridSize.x*y+x)];
}

std::optional<Tile>* Grid::operator[](int index) {
    return &tilemap[index];
}
