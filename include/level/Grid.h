#ifndef GRID_H
#define GRID_H
#include "Tile.h"
#include "TileInfo.h"
#include "SFML/Graphics.hpp"

class Grid {
public:
    Grid(sf::Vector2i tileSize);

    sf::Vector2i getTileSize();
    void setTile(int x, int y, Tile tile);
    void setTile(sf::Vector2i pos, Tile tile);
    void setTileInfo(int x, int y, TileInfo tile);
    void setTileInfo(sf::Vector2i pos, TileInfo tile);


private:
    sf::Vector2i tileSize; //tile size in pixel
};

#endif //GRID_H
