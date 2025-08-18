#ifndef PIXELPERFECTRENDERTARGET_H
#define PIXELPERFECTRENDERTARGET_H
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

class PixelPerfectRenderTarget : public sf::Drawable{
public:
    ~PixelPerfectRenderTarget() override;

    void create(unsigned windowWidth,unsigned windowHeight, int pixelSize);

    void clear(sf::Color color);
    void draw(const Drawable &drawable);
    void display();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void zoom(float amount);
    float getZoom() const {
        return zoomValue;
    }

    sf::RenderTexture* const getRenderTexture() const { return renderTexture; }

private:
    int pixelSize;
    sf::RenderTexture* renderTexture = nullptr;
    sf::Vector2u windowSize;
    float zoomValue = 1.0f;
};



#endif //PIXELPERFECTRENDERTARGET_H
