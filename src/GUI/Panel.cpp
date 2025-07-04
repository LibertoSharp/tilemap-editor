#include "GUI/Panel.h"


#include "engine/Application.h"

Panel::Panel(Vector2f size): GuiElement(size){

}

void Panel::update() {
    PanelUpdateContext ctx;
    ctx.panel = this;
    ctx.hoveringFlag = hoveringFlag;
    Update(ctx);
}

void Panel::clickDown() {
}

void Panel::clickUp() {
}
