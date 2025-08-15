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
        bool f_globalclickdown = false;
        bool f_globalclickup = false;
        bool f_deep_hovering = false;
        bool f_clickDown = false;
        bool f_clickUp = false;
        bool f_mouseDown = false;
        bool is_inside_window = false;
        float mouse_wheel_delta = 0;

        void ResetFlags() {
            f_hovering = false;
            f_deep_hovering = false;
            f_clickDown = false;
            f_clickUp = false;
            f_mouseDown = false;
            f_globalclickdown = false;
            f_globalclickup = false;
            is_inside_window = false;
            mouse_wheel_delta = 0;
        }
    };


    class GuiElement : public Drawable, public Transformable {
    public:
        GuiElement(Drawable* sprite);
        GuiElement(Vector2f size);
        virtual ~GuiElement();

        void draw(RenderTarget& target, RenderStates states) const override;
        Sprite* getActiveSprite() const {if (auto sprite = dynamic_cast<sf::Sprite*>(activeGraphic)) return sprite; return nullptr;}
        FloatRect getBoundingBox(const Drawable *graphic) const;

        Vector2f getCenter();

        bool isInsideBoundingBox(Vector2i mousePos);

        //Virtual Methdos
        virtual void update(); //called every frame
        void SetOriginByAnchor(AnchorType anchor);

        std::function<void(GuiElementEventContext)> Update = nullptr;

        //Hierarchy
        void setParent(GuiLayer* parent);
        const Drawable *getParent() const;
        std::vector<GuiElement*> getChildrens() const;
        Transform getParentTransform() const;

        Transform getGlobalTransform() const;

        Vector2f getGlobalScale() const;

        std::vector<GuiElement *> *getChildren();
        void append(GuiElement *element);

        void hide() {hideFlag = true;}
        bool isHidden() const;

        FloatRect transformRect(const sf::FloatRect &rect, const sf::Transform &transform);

        RectangleShape *getRectangleShape();

        void show() {hideFlag = false;}
        void destroy();

        void setAnchor(AnchorType anchor);
        Vector2f getPositionRelativeToAnchor(AnchorType anchor) const;
        void setRelativePosition(Vector2f pos);
        Vector2f getRelativePosition();
        void normalizeScaleRelativeToParent(Vector2f scale);
        Vector2f getNormalizedScale();
        void setGlobalScale(Vector2f scale);
        void setGlobalPosition(Vector2f pos);

        Vector2f getGlobalPosition();

        void setBoundingBoxScale(Vector2f scale);
        void setBoundingBoxOffset(Vector2f offset);
        void setShader(Shader *shader);
        Shader *getShader();

        //Fields
        Drawable* defaultGraphic;
        Drawable* activeGraphic;
        GuiElementEventContext ctx;

        bool clickTransparent = false;

    protected:
        Drawable* parent = nullptr;
        Shader *shader = nullptr;
    private:
        AnchorType anchor = TopLeft;
        Vector2f relativePosition = {0,0};
        Vector2f normalizedScale = {0,0};
        bool hideFlag = false;
        std::vector<GuiElement*> children;
        Vector2f boundingBoxScale = {1,1};
        Vector2f boundingBoxOffset = {0,0};
    };
}
#endif //GUIELEMENT_H
