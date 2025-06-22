#ifndef BUTTON_H
#define BUTTON_H
#include "GuiElement.h"
#include "SFML/Graphics/Sprite.hpp"

class Button;

struct ButtonClickContext {
    Button* button;
};

class Button : public GuiElement{
public:
    Button(sf::Sprite sprite);

    void (*Perform)(ButtonClickContext ctx);

    void update() override;
    void clickDown() override;
    void clickUp() override;

    std::optional<Sprite> hovered;
    std::optional<Sprite> pressed;
};

#endif //BUTTON_H
