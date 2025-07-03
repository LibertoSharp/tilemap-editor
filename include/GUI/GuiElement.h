#ifndef GUIELEMENT_H
#define GUIELEMENT_H
#include "AnchorsType.h"
#include "SFML/Graphics.hpp"
using namespace sf;
class GuiLayer;

class GuiElement : public Drawable, public Transformable {
 public:
    GuiElement(Drawable* sprite);
    GuiElement(Vector2f size);

    void draw(RenderTarget& target, RenderStates states) const override;
    virtual void update() = 0; //called every frame
    virtual void clickDown() = 0; //called one frame when mouse left click
    virtual void clickUp() = 0; //called one frame when mouse left click
    void setParent(GuiLayer* parent);
    Sprite* getActiveSprite() const {if (auto sprite = dynamic_cast<sf::Sprite*>(activeGraphic)) return sprite; return nullptr;}
    void Hide() {hideFlag = true;}
    void Show() {hideFlag = false;}
    bool isHidden() const {return hideFlag;}
    bool Append(GuiElement& element);
    bool isInsideBoundingBox(Vector2i mousePos);

    void SetAnchor(AnchorType anchor);
    void SetRelativePosition(Vector2f pos);
    Vector2f GetRelativePosition();

    Drawable* defaultGraphic;
    Drawable* activeGraphic;
    bool hoveringFlag = false;
    bool mouseDownFlag = false;

private:
    GuiLayer* parent;
    AnchorType anchor = TopLeft;
    Vector2f relativePosition = {0,0};
    bool hideFlag = false;
    std::vector<GuiElement*> children;
};



#endif //GUIELEMENT_H
