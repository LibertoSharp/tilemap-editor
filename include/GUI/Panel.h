#ifndef PANEL_H
#define PANEL_H
#include "GuiElement.h"


class Panel : public GuiElement{
public:
    Panel(Vector2f size);

    RectangleShape* GetRectangleShape() {
        return dynamic_cast<RectangleShape*>(activeGraphic);
    }

    void update() override;
    void clickDown() override;
    void clickUp() override;
};



#endif //PANEL_H
