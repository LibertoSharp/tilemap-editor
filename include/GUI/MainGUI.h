#ifndef MAINMENU_H
#define MAINMENU_H
#include "Button.h"
#include "GuiLayer.h"

inline void FileButton(ButtonClickContext ctx) {
    ctx.button->Hide();
}

inline GuiLayer createMainMenu() {
    GuiLayer menu;

    Button* startButton = new Button(Application::getInstance()->getTextureManager()->getSprite("GUI00",
            IntRect(Vector2i(0,0),Vector2i(32,11))));
    startButton->hovered = Application::getInstance()->getTextureManager()->getSprite("GUI00",
            IntRect(Vector2i(0,13),Vector2i(32,11)));
    startButton->setScale({2,2});
    startButton->Perform = &FileButton;

    menu.AddElement(startButton);

    return menu;
}



#endif