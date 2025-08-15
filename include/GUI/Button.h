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
        void addText(const Font *font, std::string text);
        void centerText();
        Text* getText();

        void draw(RenderTarget &target, RenderStates states) const override;

        std::optional<Sprite> hovered;
        std::optional<Sprite> pressed;
        sf::Text *text = nullptr;
    };
}

#endif //BUTTON_H
