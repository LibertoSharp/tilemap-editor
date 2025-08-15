#ifndef BUTTON_H
#define BUTTON_H
#include "GuiElement.h"
#include "SFML/Graphics/Sprite.hpp"

namespace gui {
    class Button : public GuiElement{
    public:
        explicit Button(sf::Sprite sprite);
        explicit Button(Vector2f size);
        ~Button();

        void update() override;
        void addText(const Font *font, std::string text, Color c = sf::Color::White);
        void centerText();
        Text* getText();

        void draw(RenderTarget &target, RenderStates states) const override;

        std::optional<Sprite> hovered;
        std::optional<Sprite> pressed;
        sf::Text *text = nullptr;
        Color textColor;
        Color hoveredColor;
    };
}

#endif //BUTTON_H
