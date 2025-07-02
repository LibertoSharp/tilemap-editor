#include "GUI/Button.h"

#include <iostream>
#include <utility>

Button::Button(sf::Sprite sprite): GuiElement(new Sprite(std::move(sprite))) {
}

void Button::update() {
    if (pressed.has_value() && mouseDownFlag) {
        activeGraphic = &pressed.value();
    }
    else if (hovered.has_value() && hoveringFlag)
        activeGraphic = &hovered.value();
    else
        activeGraphic = defaultGraphic;
}

void Button::clickDown() {

}

void Button::clickUp() {
    ButtonClickContext ctx;
    ctx.button = this;
    if (Perform) Perform(ctx);
}
