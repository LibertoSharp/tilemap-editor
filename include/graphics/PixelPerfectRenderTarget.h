#ifndef PIXELPERFECTRENDERTARGET_H
#define PIXELPERFECTRENDERTARGET_H
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

class PixelPerfectRenderTarget : public sf::Drawable{
public:
    ~PixelPerfectRenderTarget() override;

    void create(unsigned windowWidth,unsigned windowHeight, int pixelSize);

    void clear(sf::Color color);
    void draw(sf::Drawable &drawable);
    void display();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void zoom(float amount);
private:
    int pixelSize;
    sf::RenderTexture* renderTexture;
    sf::Vector2u windowSize;
};



#endif //PIXELPERFECTRENDERTARGET_H
