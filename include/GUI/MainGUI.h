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
    menu.AddElement(fileButton);
    fileButton->Perform = &FileButton;

    Panel* panel = new Panel({100,100});
    panel->setPosition({50,00});
    panel->GetRectangleShape()->setFillColor(Color::Blue);
    menu.AddElement(panel);


    return menu;
}



#endif