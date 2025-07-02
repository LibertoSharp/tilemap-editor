#include "GUI/GuiElement.h"

#include <iostream>
#include <utility>

GuiElement::GuiElement(Drawable* graphic): defaultGraphic(graphic), activeGraphic(defaultGraphic)  {
    childrens.reserve(3);
}

GuiElement::GuiElement(Vector2f size) : defaultGraphic(new RectangleShape(size)), activeGraphic(defaultGraphic){
    childrens.reserve(3);
}

void GuiElement::draw(RenderTarget &target, RenderStates states) const {
    if (isHidden()) return;

    states.transform *= getTransform();
    target.draw(*activeGraphic, states);

    for (auto child: childrens) {
        target.draw(*child->activeGraphic, states);
    }
}

bool GuiElement::Append(GuiElement &element) {
    childrens.push_back(&element);
}

bool GuiElement::isInsideBoundingBox(Vector2i mousePos) {
    FloatRect boundingBox;
    if (auto graphics = dynamic_cast<Sprite*>(activeGraphic)) boundingBox = graphics->getGlobalBounds();
    else if (auto graphics = dynamic_cast<Shape*>(activeGraphic)) boundingBox = graphics->getGlobalBounds();
    else return false;

    boundingBox.size = boundingBox.size.componentWiseMul(getScale());
    boundingBox.position += getPosition();
    return boundingBox.contains(Vector2<float>(mousePos));
}
