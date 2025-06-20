#include "graphics/PixelPerfectRenderTarget.h"
#include "SFML/Graphics/Sprite.hpp"

PixelPerfectRenderTarget::~PixelPerfectRenderTarget() {
    delete renderTexture;
}

void PixelPerfectRenderTarget::create(unsigned windowWidth, unsigned windowHeight, int pixelSize) {
    this->pixelSize = pixelSize;
    this->windowSize = sf::Vector2u(windowWidth, windowHeight);
    renderTexture = new sf::RenderTexture({windowWidth/pixelSize,windowHeight/pixelSize});
    renderTexture->setSmooth(false);
    zoom(1.0f);
}

void PixelPerfectRenderTarget::clear(sf::Color color) {
    renderTexture->clear(color);
}

void PixelPerfectRenderTarget::draw(const sf::Drawable &drawable) {
    renderTexture->draw(drawable);
}

void PixelPerfectRenderTarget::display() {
    renderTexture->display();
}

void PixelPerfectRenderTarget::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite sprite = sf::Sprite(renderTexture->getTexture());
    sprite.scale(sf::Vector2f(pixelSize,pixelSize));
    target.draw(sprite, states);
}

void PixelPerfectRenderTarget::zoom(float amount) {
    renderTexture->setView(sf::View(sf::FloatRect(sf::Vector2f(0,0), sf::Vector2f(windowSize.x/amount,windowSize.y/amount))));
    zoomValue = amount;
}
