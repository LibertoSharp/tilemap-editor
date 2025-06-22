#ifndef GUIELEMENT_H
#define GUIELEMENT_H
#include "SFML/Graphics.hpp"
using namespace sf;

class GuiElement : public Drawable, public Transformable {
 public:
    GuiElement(sf::Sprite sprite);

    void draw(RenderTarget& target, RenderStates states) const override;
    virtual void update() = 0; //called every frame
    virtual void clickDown() = 0; //called one frame when mouse left click
    virtual void clickUp() = 0; //called one frame when mouse left click
    Sprite* getActiveSprite() const {return activeSprite;}
    void Hide() {hideFlag = true;}
    void Show() {hideFlag = false;}
    bool isHidden() const {return hideFlag;}

    bool isInsideBoundingBox(Vector2i mousePos);

    Sprite defaultSprite;
    Sprite* activeSprite;
    bool hoveringFlag = false;
    bool mouseDownFlag = false;
private:
    bool hideFlag = false;
};



#endif //GUIELEMENT_H
