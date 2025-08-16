#ifndef LEVEL_H
#define LEVEL_H
#include "Grid.h"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderStates.hpp"

using namespace sf;

class Level final : public Drawable {
public:
    Level(unsigned int tileSize, unsigned int width, unsigned int height);

    void draw(RenderTarget& target, RenderStates states) const override;
    void createGrid(unsigned tileSize, unsigned width, unsigned height);
    Grid* getGrid() const{
        return grid;
    }

private:
    Grid* grid = nullptr;
};



#endif //LEVEL_H
