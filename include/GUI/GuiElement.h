#ifndef GUIELEMENT_H
#define GUIELEMENT_H
#include <functional>

#include "AnchorsType.h"
#include "SFML/Graphics.hpp"
namespace gui {
    using namespace sf;
    class GuiLayer;
    class GuiElement;

    struct GuiElementEventContext {
        GuiElement* element = nullptr;
        sf::Vector2i mousePos;
        bool f_hovering = false;
        bool f_deep_hovering = false;
        bool f_clickDown = false;
        bool f_clickUp = false;
        bool f_mouseDown = false;

        void ResetFlags() {
            f_hovering = false;
            f_deep_hovering = false;
            f_clickDown = false;
            f_clickUp = false;
            f_mouseDown = false;
        }
    };


    class GuiElement : public Drawable, public Transformable {
    public:
        GuiElement(Drawable* sprite);
        GuiElement(Vector2f size);

        void draw(RenderTarget& target, RenderStates states) const override;
        Sprite* getActiveSprite() const {if (auto sprite = dynamic_cast<sf::Sprite*>(activeGraphic)) return sprite; return nullptr;}
        FloatRect getBoundingBox(const Drawable *graphic) const;
        bool isInsideBoundingBox(Vector2i mousePos);

        //Virtual Methdos
        virtual void update(); //called every frame
       std::function<void(GuiElementEventContext)> Update = nullptr;

        //Hierarchy
        void setParent(GuiLayer* parent);
        const Drawable *getParent() const;
        Transform getParentTransform() const;
        Vector2f getGlobalScale() const;

        std::vector<std::weak_ptr<GuiElement>> *getChildren();
        void Append(std::shared_ptr<GuiElement> element);

        void Hide() {hideFlag = true;}
        bool isHidden() const {return hideFlag;}
        void Show() {hideFlag = false;}

        void SetAnchor(AnchorType anchor);
        Vector2f GetPositionRelativeToAnchor(AnchorType anchor) const;
        void SetRelativePosition(Vector2f pos);
        Vector2f GetRelativePosition();
        void NormalizeScaleRelativeToParent(Vector2f scale);
        Vector2f GetNormalizedScale();
        void SetGlobalScale(Vector2f scale);


        //Fields
        Drawable* defaultGraphic;
        Drawable* activeGraphic;
        GuiElementEventContext ctx;

    protected:
        Drawable* parent = nullptr;

    private:
        AnchorType anchor = TopLeft;
        Vector2f relativePosition = {0,0};
        Vector2f normalizedScale = {0,0};
        bool hideFlag = false;
        std::vector<std::weak_ptr<GuiElement>> children;
    };
}
#endif //GUIELEMENT_H
