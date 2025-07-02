#include "GUI/GuiLayer.h"

#include <iostream>

GuiLayer::GuiLayer(int reserveAmount) {
    elements.reserve(reserveAmount);
}

void GuiLayer::AddElement(GuiElement* element) {
    elements.push_back(element);
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
