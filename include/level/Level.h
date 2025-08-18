#ifndef LEVEL_H
#define LEVEL_H
#include <map>

#include "Grid.h"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderStates.hpp"

using namespace sf;

class Level final : public Drawable {
public:
    Level(unsigned int tileSize, unsigned int width, unsigned int height);

    void draw(RenderTarget& target, RenderStates states) const override;
    Grid* getGrid(int layerIndex) {
        if (grids.find(layerIndex) == grids.end())
            grids[layerIndex] = new Grid(tileSize, Vector2i(width, height));
        return grids[layerIndex];
    }

    unsigned int getTileSize() const { return tileSize;}
private:
    std::map<int, Grid*> grids;
    unsigned int tileSize = 0;
    unsigned int width = 0;
    unsigned int height = 0;
};



#endif //LEVEL_H
