#ifndef GUIELEMENT_H
#define GUIELEMENT_H
#include "SFML/Graphics.hpp"
using namespace sf;

class GuiElement : public Drawable, public Transformable {
 public:
    GuiElement(Drawable* sprite);
    GuiElement(Vector2f size);

    void draw(RenderTarget& target, RenderStates states) const override;
    virtual void update() = 0; //called every frame
    virtual void clickDown() = 0; //called one frame when mouse left click
    virtual void clickUp() = 0; //called one frame when mouse left click
    Sprite* getActiveSprite() const {if (auto sprite = dynamic_cast<sf::Sprite*>(activeGraphic)) return sprite; return nullptr;}
    void Hide() {hideFlag = true;}
    void Show() {hideFlag = false;}
    bool isHidden() const {return hideFlag;}
    bool Append(GuiElement& element);

    bool isInsideBoundingBox(Vector2i mousePos);

    Drawable* defaultGraphic;
    Drawable* activeGraphic;
    bool hoveringFlag = false;
    bool mouseDownFlag = false;
private:
    bool hideFlag = false;
    std::vector<GuiElement*> childrens;
};



#endif //GUIELEMENT_H
