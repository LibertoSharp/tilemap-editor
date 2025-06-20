#ifndef LEVEL_H
#define LEVEL_H
#include "Grid.h"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderStates.hpp"

using namespace sf;

class Level : public Drawable {
public:
    void draw(RenderTarget& target, RenderStates states) const override;
    void createGrid(unsigned tileSize, unsigned width, unsigned height);
    Grid* getGrid() const{
        return grid;
    }

private:
    Grid* grid;
};



#endif //LEVEL_H
