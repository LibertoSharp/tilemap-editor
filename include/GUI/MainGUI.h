#ifndef MAINMENU_H
#define MAINMENU_H
#include "Button.h"
#include "GuiLayer.h"
#include "Panel.h"
#include "Common.h"

static Panel* panel;

inline void FileButton(ButtonClickContext ctx) {
    if (panel->isHidden())panel->Show();
    else panel->Hide();
}

inline void PanelHover(PanelUpdateContext ctx) {
    if (ctx.hoveringFlag)
        ctx.panel->SetRelativePosition(Damp(ctx.panel->GetRelativePosition(), Vector2f(-200,0),1.0f,Application::getInstance()->getDeltaTime()));
    else ctx.panel->SetRelativePosition(Damp(ctx.panel->GetRelativePosition(), Vector2f(0,0),1.0f,Application::getInstance()->getDeltaTime()));
}


inline GuiLayer* createMainMenu() {
    GuiLayer* menu = new GuiLayer();

    Button* fileButton = new Button(Application::getInstance()->getTextureManager()->getSprite("GUI00",
            IntRect(Vector2i(0,0),Vector2i(32,11))));
    fileButton->hovered = Application::getInstance()->getTextureManager()->getSprite("GUI00",
            IntRect(Vector2i(0,13),Vector2i(32,11)));
    fileButton->setScale({2,2});
    fileButton->Perform = &FileButton;
    menu->AddElement(fileButton);


    panel = new Panel({300,300});
    panel->setOrigin({100,0});
    panel->SetAnchor(TopRight);
    panel->SetRelativePosition({0,0});
    panel->GetRectangleShape()->setFillColor(Color(0,0,0,200));
    panel->NormalizePositionRelativeToParent({0,1});
    panel->Update = &PanelHover;
    menu->AddElement(panel);

    return menu;
}



#endif