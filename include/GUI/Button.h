#ifndef BUTTON_H
#define BUTTON_H
#include "GuiElement.h"
#include "SFML/Graphics/Sprite.hpp"

namespace gui {
    class Button : public GuiElement{
    public:
        Button(sf::Sprite sprite);
        ~Button() = default;

        void update() override;

        std::optional<Sprite> hovered;
        std::optional<Sprite> pressed;
    };
}

#endif //BUTTON_H
