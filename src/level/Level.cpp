#include "level/Level.h"

#include "SFML/Graphics/RenderTarget.hpp"

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

void Level::createGrid(unsigned tileSize, unsigned width, unsigned height) {
    grid = new Grid(tileSize, Vector2i(width, height));
}
