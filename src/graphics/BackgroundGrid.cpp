#include "graphics/BackgroundGrid.h"

#include "engine/Application.h"

BackgroundGrid::BackgroundGrid(unsigned int tileSize, unsigned int width, unsigned int height)
{
    sf::Color gridColor = sf::Color(175, 175, 175,120);
    gridLines.setPrimitiveType(sf::PrimitiveType::Lines);

    for (int x = 0; x < width; x++) {
        gridLines.append({{static_cast<float>(x*tileSize),0}, gridColor,{0,0}});
        gridLines.append({{static_cast<float>(x*tileSize),static_cast<float>(height*tileSize)}, gridColor,{1,1}});
    }
    for (int y = 0; y < height; y++) {
        gridLines.append({{0,static_cast<float>(y*tileSize)}, gridColor,{0,0}});
        gridLines.append({{static_cast<float>(width*tileSize),static_cast<float>(y*tileSize)}, gridColor,{1,1}});
    }
}

void BackgroundGrid::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    unsigned int zoom = Application::getInstance()->getRenderTarget()->getZoom();
    states.transform.scale({static_cast<float>(zoom),static_cast<float>(zoom)});
    target.draw(gridLines, states);
}
