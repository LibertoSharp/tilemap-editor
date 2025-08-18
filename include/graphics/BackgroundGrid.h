#ifndef BACKGROUNDGRID_H
#define BACKGROUNDGRID_H
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/VertexArray.hpp"

class BackgroundGrid : public sf::Drawable {
public:
	BackgroundGrid(unsigned int tileSize, unsigned int width, unsigned int height);

protected:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
	sf::VertexArray gridLines;
};
#endif //BACKGROUNDGRID_H
