#include "level/Level.h"

#include "engine/Application.h"
#include "SFML/Graphics/RenderTarget.hpp"

Level::Level(unsigned int tileSize, unsigned int width, unsigned int height) {
    this->tileSize = tileSize;
    this->width = width;
    this->height = height;
    grids[0] = new Grid(tileSize, Vector2i(width, height));
    background = new BackgroundGrid(tileSize, width, height);
}

Level::~Level() {
    for (auto [key,grid]: grids) {
        delete grid;
    }
}

void Level::draw(RenderTarget &target, RenderStates states) const {
    for (auto [index, grid]: grids) {
        for (int x = 0; x < grid->getGridSize().x; x++) {
            for (int y = 0; y < grid->getGridSize().y; y++) {
                int index = x * grid->getTileSize()+y;

                if (!(*grid)[index]->has_value()) continue;

                Sprite *sprite = (*grid)[index]->value().getSprite();
                target.draw(*sprite);
            }
        }
    }
}

BackgroundGrid * Level::getBackgroundGrid() {
    return background;
}
