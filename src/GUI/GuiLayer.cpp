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
    for (const auto element : elements) {
        if (element->isHidden()) return;

        if (element->isInsideBoundingBox(ctx.mousePos)) {
            if (ctx.clickDown) element->clickDown();
            if (ctx.clickUp) element->clickUp();

            element->mouseDownFlag = ctx.mouseDown;
            element->hoveringFlag = true;
        } else {
            element->mouseDownFlag = false;
            element->hoveringFlag = false;
        }

        element->update();
    }
}
