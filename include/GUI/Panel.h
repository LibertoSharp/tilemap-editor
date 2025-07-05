#ifndef PANEL_H
#define PANEL_H
#include "GuiElement.h"
namespace gui {
    class Panel : public GuiElement{
    public:
        Panel(Vector2f size);

        RectangleShape* GetRectangleShape() {
            return dynamic_cast<RectangleShape*>(activeGraphic);
        }
    };
}


#endif //PANEL_H
