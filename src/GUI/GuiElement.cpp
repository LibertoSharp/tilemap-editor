#include "GUI/GuiElement.h"

#include <iostream>

GuiElement::GuiElement(sf::Sprite sprite): defaultSprite(sprite), activeSprite(&defaultSprite)  {

}

void GuiElement::draw(RenderTarget &target, RenderStates states) const {
    if (isHidden()) return;

    states.transform *= getTransform();
    target.draw(*activeSprite, states);
}

bool GuiElement::isInsideBoundingBox(Vector2i mousePos) {
    FloatRect boundingBox = activeSprite->getGlobalBounds();
    boundingBox.size = boundingBox.size.componentWiseMul(getScale());
    return boundingBox.contains(Vector2<float>(mousePos));
}
