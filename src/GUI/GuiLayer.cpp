#include "GUI/GuiLayer.h"
#include "engine/Application.h"

GuiLayer::GuiLayer(int reserveAmount) {
    elements.reserve(reserveAmount);
    this->window = Application::getInstance()->getWindow();
}

GuiLayer::GuiLayer(Window* window, int reserveAmount) {
    elements.reserve(reserveAmount);
    this->window = window;
}

void GuiLayer::AddElement(GuiElement* element) {
    elements.push_back(element);
    element->setParent(this);
    element->SetRelativePosition(element->GetRelativePosition());
}

void GuiLayer::RemoveElement(GuiElement* element) {
    for (auto it = elements.begin(); it != elements.end(); it++) {
        if (*it == element) {
            elements.erase(it);
            delete element;
        }
    }
}

void GuiLayer::RemoveAllElements() {
    for (auto element : elements) {
        delete element;
    }
    elements.clear();
}


Vector2f GuiLayer::GetPositionRelativeToAnchor(AnchorType anchor) {
    switch (anchor) {
        case TopLeft: return {0, 0};
        case TopRight: return {window->getSize().x,0};
        case TopCenter: return {window->getSize().x/2.0, 0};
        case MiddleLeft: return {0,window->getSize().y/2.0};
        case MiddleCenter: return {window->getSize().x/2.0, window->getSize().y/2.0};
        case MiddleRight: return {window->getSize().x,window->getSize().y/2.0};
        case BottomLeft: return {0,window->getSize().y};
        case BottomCenter: return {window->getSize().x/2,window->getSize().y};
        case BottomRight: return {window->getSize().x,window->getSize().y};
    }
}

void GuiLayer::draw(RenderTarget &target, RenderStates states) const {
    for (const auto element : elements) {
        target.draw(*element, states);
    }
}

void callEventsInternal(GuiElement* element, GuiEventContext ctx) {
    if (ctx.clickDown) element->clickDown();
    if (ctx.clickUp) element->clickUp();

    element->mouseDownFlag = ctx.mouseDown;
    element->hoveringFlag = true;
}

void GuiLayer::callEvents(GuiEventContext ctx) {
    bool first = true;
    for (const auto element : std::vector<GuiElement*>(elements.rbegin(), elements.rend())) {
        for (const auto child : std::vector<GuiElement*>(element->getChildren()->rbegin(), element->getChildren()->rend())) {
            if (child->isHidden()) continue;

            if (child->isInsideBoundingBox(ctx.mousePos) && first) {
                callEventsInternal(child, ctx);
                first = false;
            } else {
                child->mouseDownFlag = false;
                child->hoveringFlag = false;
            }

            child->update();
        }
        if (element->isInsideBoundingBox(ctx.mousePos) && first) {
            if (element->isHidden()) continue;


            callEventsInternal(element, ctx);
            first = false;
        } else {
            element->mouseDownFlag = false;
            element->hoveringFlag = false;
        }

            element->update();
        }
    }

