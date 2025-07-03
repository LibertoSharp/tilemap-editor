#include "GUI/GuiElement.h"
#include "GUI/GuiLayer.h"

GuiElement::GuiElement(Drawable* graphic): defaultGraphic(graphic), activeGraphic(defaultGraphic)  {
    children.reserve(3);
}

GuiElement::GuiElement(Vector2f size) : defaultGraphic(new RectangleShape(size)), activeGraphic(defaultGraphic){
    children.reserve(3);
}

void GuiElement::draw(RenderTarget &target, RenderStates states) const {
    if (isHidden()) return;

    states.transform *= getTransform();
    target.draw(*activeGraphic, states);

    for (auto child: children) {
        target.draw(*child->activeGraphic, states);
    }
}

void GuiElement::setParent(GuiLayer *parent) {
    this->parent = parent;
}

bool GuiElement::Append(GuiElement &element) {
    children.push_back(&element);
}

bool GuiElement::isInsideBoundingBox(Vector2i mousePos) {
    FloatRect boundingBox;
    if (auto graphics = dynamic_cast<Sprite*>(activeGraphic)) boundingBox = graphics->getGlobalBounds();
    else if (auto graphics = dynamic_cast<Shape*>(activeGraphic)) boundingBox = graphics->getGlobalBounds();
    else return false;

    boundingBox.size = boundingBox.size.componentWiseMul(getScale());
    boundingBox.position += getPosition();
    boundingBox.position -= getOrigin();
    return boundingBox.contains(Vector2<float>(mousePos));
}

void GuiElement::SetAnchor(AnchorType anchor) {
    this->anchor = anchor;
}

void GuiElement::SetRelativePosition(Vector2f pos) {
    relativePosition = pos;

    if (!parent) return;

    Vector2f anchorPos = parent->GetPositionRelativeToAnchor(anchor);
    setPosition(anchorPos+pos);
}

Vector2f GuiElement::GetRelativePosition() {
    return relativePosition;
}
