#ifndef BACKGROUNDGRID_H
#define BACKGROUNDGRID_H
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/VertexArray.hpp"

class Level;

class BackgroundGrid : public sf::Drawable {
public:
	BackgroundGrid(unsigned int tileSize, unsigned int width, unsigned int height, Level *level);

protected:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
	sf::VertexArray gridLines;
	Level *level;
};
#endif //BACKGROUNDGRID_H
