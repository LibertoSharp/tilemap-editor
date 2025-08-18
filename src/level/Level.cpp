#include "level/Level.h"

#include "SFML/Graphics/RenderTarget.hpp"

Level::Level(unsigned int tileSize, unsigned int width, unsigned int height) {
    this->tileSize = tileSize;
    createGrid(tileSize, width, height);
}

void Level::draw(RenderTarget &target, RenderStates states) const {
    for (int x = 0; x < grid->getGridSize().x; x++) {
        for (int y = 0; y < grid->getGridSize().y; y++) {
            int index = x * grid->getTileSize()+y;

            if (!(*grid)[index]->has_value()) continue;

            Sprite* sprite = (*grid)[index]->value().getSprite();
            target.draw(*sprite);
        }
    }
}

void Level::createGrid(unsigned int tileSize, unsigned int width, unsigned int height) {
    grid = new Grid(tileSize, Vector2i(width, height));
}
