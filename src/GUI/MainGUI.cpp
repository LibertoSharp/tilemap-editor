#include "GUI/Dropdown.h"
#include "GUI/TextElement.h"
#include "GUI/Tilegrid.h"
#ifndef MAINMENU_H
#define MAINMENU_H
#include "../../include/GUI/Button.h"
#include "../../include/GUI/GuiLayer.h"
#include "../../include/GUI/Panel.h"
#include "../../include/GUI/Common.h"
#include  "engine/Application.h"
using namespace gui;
static Dropdown* fileButton;
static Dropdown* editButton;
static Panel* editPanel;
static Sprite getGuiSprite(std::string atlasid,int posx, int posy, int width, int height) {
    return Application::getInstance()->getTextureManager()->getSprite(atlasid, posx, posy, width, height);
}

namespace gui {
    inline void EditButton(GuiElementEventContext ctx) {
        if (ctx.f_clickDown) {
            if (editPanel->isHidden()) editPanel->show();
            else editPanel->hide();
        }
    }

    inline void FileValueChanged(int index) {
        std::cout << index << std::endl;
    }

    inline void PanelHover(GuiElementEventContext ctx) {
        Panel* panel = dynamic_cast<Panel*>(ctx.element);
        if (ctx.f_deep_hovering)
            panel->setRelativePosition(damp(panel->getRelativePosition(), Vector2f(-200,0),1.0f,Application::getInstance()->getDeltaTime()));
        else panel->setRelativePosition(damp(panel->getRelativePosition(), Vector2f(0,0),1.0f,Application::getInstance()->getDeltaTime()));
    }

    inline GuiLayer* createMainMenu() {
        GuiLayer* menu = new GuiLayer();

        //FILE BUTTON
        fileButton = new Dropdown(getGuiSprite("GUI00", 0, 0, 36,12));
        fileButton->hovered = getGuiSprite("GUI00",0,13,36,12);
        fileButton->setGlobalScale({2,2});
        fileButton->addEntry(getGuiSprite("GUI00", 0, 26, 36,12),
            getGuiSprite("GUI00", 0, 39, 36,12));
        fileButton->addEntry(getGuiSprite("GUI00", 0, 52, 36,12),
            getGuiSprite("GUI00", 0, 65, 36,12));
        fileButton->ValueChanged = &FileValueChanged;
        menu->addElement(fileButton, true);

        //FILE PANEL
        editPanel = new Panel({300,300});
        editPanel->hide();
        editPanel->setOrigin({100,0});
        editPanel->setAnchor(TopRight);
        editPanel->setRelativePosition({0,0});
        editPanel->getRectangleShape()->setFillColor(Color(0,0,0,200));
        editPanel->normalizeScaleRelativeToParent({0,1});
        editPanel->Update = &PanelHover;
        menu->addElement(editPanel, false);

        //EDIT BUTTON
        editButton = new Dropdown(getGuiSprite("GUI00", 36, 0, 36,12));
        editButton->hovered = getGuiSprite("GUI00", 36, 13, 36,12);\
        editButton->Update = &EditButton;
        editButton->setGlobalScale({2,2});
        editButton->setPosition({36*2,0});
        menu->addElement(editButton, true);

        TextElement* t = new TextElement(Application::getInstance()->getFontManager()->getFont("PixelOperator8"), "Hiii");
        t->setPosition({100,100});
        t->setFillColor(Color(255,0,0,200));
        menu->addElement(t, true);

        Tilegrid* tilegrid = new Tilegrid(Application::getInstance()->getTextureManager()->getAtlasTexture("tileset\\plains"), {16,16});
        editPanel->append(tilegrid);
        tilegrid->setGlobalScale({2,2});

        return menu;
    }
}


#endif