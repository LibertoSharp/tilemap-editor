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
    }
}

void GuiLayer::draw(RenderTarget &target, RenderStates states) const {
    for (const auto element : elements) {
        target.draw(*element, states);
    }
}

void GuiLayer::callEvents(GuiEventContext ctx) {
    bool first = true;
    for (const auto element : std::vector<GuiElement*>(elements.rbegin(), elements.rend())) {
        if (element->isHidden()) continue;

        if (element->isInsideBoundingBox(ctx.mousePos) && first) {
            if (ctx.clickDown) element->clickDown();
            if (ctx.clickUp) element->clickUp();

            element->mouseDownFlag = ctx.mouseDown;
            element->hoveringFlag = true;
            first = false;
        } else {
            element->mouseDownFlag = false;
            element->hoveringFlag = false;
        }

        element->update();
    }
}
