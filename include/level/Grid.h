#ifndef GRID_H
#define GRID_H
#include <set>

#include "Tile.h"
#include "TileInfo.h"
#include "SFML/Graphics.hpp"

class Grid {
public:
    Grid(unsigned tileSize, sf::Vector2i gridSize);

    unsigned getTileSize() const;
    sf::Vector2i getGridSize() const;

    void setTile(int x, int y, std::optional<Tile> tile);
    void setTile(sf::Vector2i pos, std::optional<Tile> tile);
    void setTileInfo(int x, int y, TileInfo tile);
    void setTileInfo(sf::Vector2i pos, TileInfo tile);
    std::set<std::string> getTileset();
    std::optional<Tile> getTile(int x, int y);
    std::optional<Tile>* operator [](int index);

private:
    unsigned tileSize; //tile size in pixel
    sf::Vector2i gridSize; //grid size in tiles
    std::vector<std::optional<Tile>> tilemap;
    std::set<std::string> tilesets;
};

#endif //GRID_H
