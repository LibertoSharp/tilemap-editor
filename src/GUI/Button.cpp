#include "GUI/Button.h"

#include <iostream>
#include <utility>
namespace gui {
    Button::Button(sf::Sprite sprite): GuiElement(new Sprite(std::move(sprite))) {}
    Button::Button(Vector2f size): GuiElement(size) {}

    Button::~Button() {
        if (text)
            delete text;
    }

    void Button::update() {
        if (text != nullptr)
        if (ctx.f_hovering)
            text->setFillColor(hoveredColor);
        else
            text->setFillColor(textColor);

        if (pressed.has_value() && ctx.f_mouseDown) {
            activeGraphic = &pressed.value();
        }
        else if (hovered.has_value() && ctx.f_hovering)
            activeGraphic = &hovered.value();
        else
            activeGraphic = defaultGraphic;

        GuiElement::update();
    }

    void Button::addText(const Font *font, std::string text, Color c) {
        this->text = new Text(*font, text);
        textColor = c;
        hoveredColor = {static_cast<unsigned char>(textColor.r * 0.75f), static_cast<unsigned char>(textColor.g * 0.75f), static_cast<unsigned char>(textColor.b * 0.75f), textColor.a};
        this->text->setFillColor(c);
    }

    void Button::centerText() {
        text->setOrigin(text->getLocalBounds().getCenter());
        text->setPosition(getCenter());
    }


    Text *Button::getText() {
        return text;
    }

    void Button::draw(RenderTarget &target, RenderStates states) const {
        if (isHidden()) return;

        states.transform *= getTransform();
        if (shader != nullptr)
            states.shader = shader;
        target.draw(*activeGraphic, states);
        if (text != nullptr)
            target.draw(*text, states);

        for (auto child: getChildrens()) {
            if (child)
                target.draw(*child, states);
        }
    }
}
