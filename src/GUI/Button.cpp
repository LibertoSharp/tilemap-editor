#include "GUI/Button.h"

#include <iostream>
#include <utility>

Button::Button(sf::Sprite sprite): GuiElement(std::move(sprite)) {
}

void Button::update() {
    if (pressed.has_value() && mouseDownFlag) {
        activeSprite = &pressed.value();
    }
    else if (hovered.has_value() && hoveringFlag)
        activeSprite = &hovered.value();
    else
        activeSprite = &defaultSprite;
}

void Button::clickDown() {

}

void Button::clickUp() {
    ButtonClickContext ctx;
    ctx.button = this;
    if (Perform) Perform(ctx);
}
