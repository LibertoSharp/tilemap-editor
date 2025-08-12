#include "GUI/GuiElement.h"

#include <algorithm>
#include <iostream>

#include "engine/Application.h"
#include "GUI/GuiLayer.h"
namespace gui {
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
            if (auto c = child.lock())
                target.draw(*c, states);
        }
    }

    void GuiElement::setParent(GuiLayer *parent) {
        this->parent = parent;
    }

    const Drawable *GuiElement::getParent() const{
        return parent;
    }

    Transform GuiElement::getParentTransform() const {
        Transform transform;
        if (auto element = dynamic_cast<GuiElement*>(parent)) { transform = element->getParentTransform().combine(getTransform());}
        else transform = getTransform();
        return transform;
    }

    Vector2f GuiElement::getGlobalScale() const {
        Vector2f scale = getScale();
        if (parent == nullptr) return scale;
        if (auto element = dynamic_cast<GuiElement*>(parent)) {
            Vector2f parentScale = element->getGlobalScale();
            scale = {scale.x * parentScale.x, scale.y * parentScale.y};
        }
        else scale = getScale();
        return scale;
    }

    void GuiElement::Append(std::shared_ptr<GuiElement> element) {
        element->parent = this;
        children.push_back(std::weak_ptr(element));
    }

    FloatRect transformRect(const sf::FloatRect& rect, const sf::Transform& transform) {
        Vector2f topLeft = transform.transformPoint(rect.position);
        Vector2f bottomRight = transform.transformPoint({rect.position.x+rect.size.x, rect.position.y+rect.size.y});

        return {topLeft,bottomRight-topLeft};
    }

    FloatRect GuiElement::getBoundingBox(const Drawable* graphic) const {
        if (auto graphics = dynamic_cast<Sprite*>(activeGraphic)) return graphics->getGlobalBounds();
        else if (auto graphics = dynamic_cast<Shape*>(activeGraphic)) return graphics->getGlobalBounds();

        std::cerr << "Couldn't get bounding box" << std::endl;
        return {};
    }

    bool GuiElement::isInsideBoundingBox(Vector2i mousePos) {
        FloatRect boundingBox = getBoundingBox(activeGraphic);
        boundingBox = transformRect(boundingBox, getParentTransform());
        return boundingBox.contains(Vector2<float>(mousePos));
    }

    void GuiElement::update() {
        if (Update) {
            ctx.element = this;
            Update(ctx);
        }
    }

    void GuiElement::SetAnchor(AnchorType anchor) {
        this->anchor = anchor;
    }

    Vector2f GuiElement::GetPositionRelativeToAnchor(AnchorType anchor) const {
        FloatRect boundingBox = getBoundingBox(activeGraphic);
        switch (anchor) {
            case TopLeft: return boundingBox.position;
            case TopCenter: return {boundingBox.position.x+boundingBox.size.x/2.0f,0};
            case TopRight: return {boundingBox.position.x+boundingBox.size.x,0};
            case MiddleLeft: return {0,boundingBox.position.y+boundingBox.size.y/2.0f};
            case MiddleCenter: return {boundingBox.position.x+boundingBox.size.x/2.0f,boundingBox.position.y+boundingBox.size.y/2.0f};
            case MiddleRight: return {boundingBox.position.x+boundingBox.size.x,boundingBox.position.y+boundingBox.size.y/2.0f};
            case BottomLeft: return {0,boundingBox.position.y+boundingBox.size.y};
            case BottomCenter: return {boundingBox.position.x+boundingBox.size.x/2.0f,boundingBox.position.y+boundingBox.size.y};
            case BottomRight: return {boundingBox.position.x+boundingBox.size.x,boundingBox.position.y+boundingBox.size.y};
        }
    }

    void GuiElement::SetRelativePosition(Vector2f pos) {
        relativePosition = pos;
        Vector2f anchorPos;

        if (!parent) return;
        if (auto layer = dynamic_cast<GuiLayer*>(parent)) anchorPos = layer->GetPositionRelativeToAnchor(anchor);
        else if (auto element = dynamic_cast<GuiElement*>(parent)) anchorPos = element->GetPositionRelativeToAnchor(anchor);
        else return;

        setPosition(anchorPos+pos);
    }

    Vector2f GuiElement::GetRelativePosition() {
        return relativePosition;
    }

    void GuiElement::NormalizeScaleRelativeToParent(Vector2f scale) {
        Vector2f size;
        normalizedScale = scale;
        if (auto layer = dynamic_cast<GuiLayer*>(parent)) size = static_cast<Vector2f>(Application::getInstance()->getWindow()->getSize());
        else if (auto element = dynamic_cast<GuiElement*>(parent)) size = element->getBoundingBox(element->activeGraphic).size;
        else return;


        float scalex = getScale().x, scaley = getScale().y;
        if (scale.x != 0)
            scalex = (size.x * scale.x)/getBoundingBox(activeGraphic).size.x;
        if (scale.y != 0)
            scaley = (size.y * scale.y)/getBoundingBox(activeGraphic).size.y;

        setScale({scalex,scaley});
    }

    Vector2f GuiElement::GetNormalizedScale() {
        return normalizedScale;
    }

    void GuiElement::SetGlobalScale(Vector2f scale) {
        Vector2f pscale = getGlobalScale();
        Vector2f localScale = getScale();
        pscale = {pscale.x/localScale.x,pscale.y/localScale.y};

        scale = {1.0f / pscale.x * scale.x, 1.0f / pscale.y * scale.y};
        setScale(scale);
    }

    std::vector<std::weak_ptr<GuiElement>> *GuiElement::getChildren() {
        return &children;
    }
}