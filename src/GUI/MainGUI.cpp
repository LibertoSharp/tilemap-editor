#ifndef MAINMENU_H
#define MAINMENU_H
#include "../../include/GUI/Button.h"
#include "../../include/GUI/GuiLayer.h"
#include "../../include/GUI/Panel.h"
#include "../../include/GUI/Common.h"
#include  "engine/Application.h"
using namespace gui;
static Button* fileButton;
static Panel* filePanel;
static Button* editButton;

namespace gui {
    inline void FileButton(GuiElementEventContext ctx) {
        if (ctx.f_clickDown) {
            if (filePanel->isHidden()) filePanel->Show();
            else filePanel->Hide();
        }
    }

    inline void PanelHover(GuiElementEventContext ctx) {
        Panel* panel = dynamic_cast<Panel*>(ctx.element);
        if (ctx.f_deep_hovering)
            panel->SetRelativePosition(Damp(panel->GetRelativePosition(), Vector2f(-200,0),1.0f,Application::getInstance()->getDeltaTime()));
        else panel->SetRelativePosition(Damp(panel->GetRelativePosition(), Vector2f(0,0),1.0f,Application::getInstance()->getDeltaTime()));
    }

    inline GuiLayer* createMainMenu() {
        GuiLayer* menu = new GuiLayer();

        //FILE BUTTON
        fileButton = new Button(Application::getInstance()->getTextureManager()->getSprite("GUI00",
                IntRect(Vector2i(0,0),Vector2i(36,12))));
        fileButton->hovered = Application::getInstance()->getTextureManager()->getSprite("GUI00",
                IntRect(Vector2i(0,13),Vector2i(36,12)));
        fileButton->SetGlobalScale({2,2});
        fileButton->Update = &FileButton;
        menu->AddElement(fileButton, true);

        //FILE PANEL
        filePanel = new Panel({300,300});
        filePanel->setOrigin({100,0});
        filePanel->SetAnchor(TopRight);
        filePanel->SetRelativePosition({0,0});
        filePanel->GetRectangleShape()->setFillColor(Color(0,0,0,200));
        filePanel->NormalizeScaleRelativeToParent({0,1});
        filePanel->Update = &PanelHover;
        menu->AddElement(filePanel, false);

        //EDIT BUTTON
        editButton = new Button(Application::getInstance()->getTextureManager()->getSprite("GUI00",
                IntRect(Vector2i(36,0),Vector2i(36,12))));
        editButton->hovered = Application::getInstance()->getTextureManager()->getSprite("GUI00",
        IntRect(Vector2i(36,13),Vector2i(36,12)));
        editButton->SetGlobalScale({2,2});
        editButton->setPosition({36*2,0});
        menu->AddElement(editButton, true);

        return menu;
    }
}


#endif