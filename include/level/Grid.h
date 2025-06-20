#ifndef GRID_H
#define GRID_H
#include "Tile.h"
#include "TileInfo.h"
#include "SFML/Graphics.hpp"

class Grid {
public:
    Grid(unsigned tileSize, sf::Vector2i gridSize);

    unsigned getTileSize() const;
    sf::Vector2i getGridSize() const;

    void setTile(int x, int y, Tile tile);
    void setTile(sf::Vector2i pos, Tile tile);
    void setTileInfo(int x, int y, TileInfo tile);
    void setTileInfo(sf::Vector2i pos, TileInfo tile);

    std::optional<Tile>* operator [](int index) const;

private:
    unsigned tileSize; //tile size in pixel
    sf::Vector2i gridSize; //grid size in tiles
    std::optional<Tile>* tilemap;
    std::optional<TileInfo>* infomap;
};

#endif //GRID_H
