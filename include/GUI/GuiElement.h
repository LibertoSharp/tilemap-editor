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
    Sprite* getActiveSprite() const {if (auto sprite = dynamic_cast<sf::Sprite*>(activeGraphic)) return sprite; return nullptr;}
    FloatRect getBoundingBox(const Drawable *graphic) const;
    bool isInsideBoundingBox(Vector2i mousePos);

    //Virtual Methdos
    virtual void update() = 0; //called every frame
    virtual void clickDown() = 0; //called one frame when mouse left click
    virtual void clickUp() = 0; //called one frame when mouse left click

    //Hierarchy
    void setParent(GuiLayer* parent);
    void setParent(GuiElement* parent);
    Transform getParentTransform() const;
    void AddChildren(GuiElement* child);
    std::vector<GuiElement*>* getChildren();
    void Append(GuiElement *element);

    void Hide() {hideFlag = true;}
    bool isHidden() const {return hideFlag;}
    void Show() {hideFlag = false;}

    void SetAnchor(AnchorType anchor);
    Vector2f GetPositionRelativeToAnchor(AnchorType anchor) const;
    void SetRelativePosition(Vector2f pos);
    Vector2f GetRelativePosition();


    //Fields
    Drawable* defaultGraphic;
    Drawable* activeGraphic;
    bool hoveringFlag = false;
    bool mouseDownFlag = false;

private:
    Drawable* parent;
    AnchorType anchor = TopLeft;
    Vector2f relativePosition = {0,0};
    bool hideFlag = false;
    std::vector<GuiElement*> children;
};

#endif //GUIELEMENT_H
