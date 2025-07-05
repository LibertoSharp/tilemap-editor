#include "GUI/Button.h"

#include <iostream>
#include <utility>
namespace gui {
    Button::Button(sf::Sprite sprite): GuiElement(new Sprite(std::move(sprite))) {}

    void Button::update() {
        if (pressed.has_value() && ctx.f_mouseDown) {
            activeGraphic = &pressed.value();
        }
        else if (hovered.has_value() && ctx.f_hovering)
            activeGraphic = &hovered.value();
        else
            activeGraphic = defaultGraphic;

        GuiElement::update();
    }
}
