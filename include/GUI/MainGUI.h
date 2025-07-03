#ifndef MAINMENU_H
#define MAINMENU_H
#include "Button.h"
#include "GuiLayer.h"
#include "Panel.h"

inline void FileButton(ButtonClickContext ctx) {
    std::cout << "File Button Clicked" << std::endl;
}

inline GuiLayer createMainMenu() {
    GuiLayer menu;

    Button* fileButton = new Button(Application::getInstance()->getTextureManager()->getSprite("GUI00",
            IntRect(Vector2i(0,0),Vector2i(32,11))));
    fileButton->hovered = Application::getInstance()->getTextureManager()->getSprite("GUI00",
            IntRect(Vector2i(0,13),Vector2i(32,11)));
    fileButton->setScale({2,2});
    fileButton->Perform = &FileButton;
    menu.AddElement(fileButton);


    Panel* panel = new Panel({100,300});
    panel->setOrigin({100,0});
    panel->SetAnchor(TopRight);
    panel->SetRelativePosition({0,0});
    panel->GetRectangleShape()->setFillColor(Color(0,0,0,200));
    menu.AddElement(panel);

    return menu;
}



#endif