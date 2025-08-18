#include "GUI/GuiLayer.h"
#include "engine/Application.h"
namespace gui {
    GuiLayer::GuiLayer(int reserveAmount) {
        elements.reserve(reserveAmount);
        this->window = Application::getInstance()->getWindow();
    }

    GuiLayer::GuiLayer(Window* window, int reserveAmount) {
        elements.reserve(reserveAmount);
        this->window = window;
    }

    void GuiLayer::addElement(GuiElement* element, bool keepWorldPos) {
        elements.push_back(element);
        element->setParent(this);
        if (!keepWorldPos)
            element->setRelativePosition(element->getRelativePosition());
        element->normalizeScaleRelativeToParent(element->getNormalizedScale());
    }

    void GuiLayer::removeElement(GuiElement* element) {
        for (auto& e : elements) {
            if (e == element) {
                e = nullptr;
            }
        }
        delete element;
    }

    void GuiLayer::removeAllElements() {
        for (auto element : elements) {
            delete element;
        }
        elements.clear();
    }


    Vector2f GuiLayer::getPositionRelativeToAnchor(AnchorType anchor) {
        float width = static_cast<float>(window->getSize().x);
        float height = static_cast<float>(window->getSize().y);
        switch (anchor) {
            case TopLeft: return {0, 0};
            case TopRight: return {width,0};
            case TopCenter: return {width/2.0f, 0};
            case MiddleLeft: return {0,height/2.0f};
            case MiddleCenter: return {width/2.0f, height/2.0f};
            case MiddleRight: return {width,height/2.0f};
            case BottomLeft: return {0,height};
            case BottomCenter: return {width/2.0f,height};
            case BottomRight: return {width,height};
        }

        return {0, 0};
    }

    void GuiLayer::draw(RenderTarget &target, RenderStates states) const {
        for (const auto element : elements) {
            target.draw(*element, states);
        }
    }

    void callEventsInternal(GuiElement* element, GuiEventContext& ctx, bool& first) {
        auto& children = *element->getChildren();
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            GuiElement *child = *it;
            if (child) {
                callEventsInternal(child, ctx, first);
            } else
                children.erase(it.base()-1);
        }

        if (element->isHidden()) return;
        GuiElementEventContext elementCtx{};
        elementCtx.mousePos = ctx.mousePos;
        elementCtx.f_globalclickdown = ctx.f_clickDown;
        elementCtx.f_globalclickup = ctx.f_clickUp;
        elementCtx.is_inside_window = ctx.is_inside_window;
        elementCtx.mouse_wheel_delta = ctx.mouse_wheel_delta;
        elementCtx.textEntered = ctx.textEntered;
        elementCtx.keyPressed = ctx.keyPressed;
        elementCtx.f_wheelClick = ctx.f_wheelClick;
        elementCtx.f_wheelDown = ctx.f_wheelDown;
        elementCtx.f_globalWheelUp = ctx.f_wheelUp;
        if (element->isInsideBoundingBox(ctx.mousePos)) {
            elementCtx.f_deep_hovering = true;
            if (first) {
                elementCtx.f_hovering = true;
                elementCtx.f_clickDown = ctx.f_clickDown;
                elementCtx.f_mouseDown = ctx.f_mouseDown;
                elementCtx.f_clickUp = ctx.f_clickUp;
                elementCtx.f_wheelUp = ctx.f_wheelUp;
                if (!element->clickTransparent)
                first = false;
            }
        }

        element->ctx = elementCtx;
        element->update();
    }

    bool GuiLayer::callEvents() {
        bool first = true;
        for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
            GuiElement *element = *it;
            if (element) {
                callEventsInternal(element, ctx, first);
            } else
                elements.erase(it.base()-1);
        }
        ctx.Reset();
        return first;
    }
}
