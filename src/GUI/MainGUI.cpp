#include "GUI/TextInput.h"
#ifndef MAINMENU_H
#define MAINMENU_H
#include <iostream>
#include "GUI/Dropdown.h"
#include "GUI/TextElement.h"
#include "GUI/Tilegrid.h"
#include "../../include/GUI/Button.h"
#include "../../include/GUI/GuiLayer.h"
#include "../../include/Common.h"
#include  "engine/Application.h"

using namespace gui;

static Dropdown *fileButton;
static Button *editButton;
static GuiElement *editPanel;
static TextElement *ModeLabel;
static Button *DrawModeButton;
static Button *EraseModeButton;
static Button *SelectModeButton;
static TextElement *TileScriptLabel;
static TextInput *TileScriptPanel;
static Button *OpenButton;
static GuiElement *OpenPathBackground;
static TextInput *OpenPathLabel;
static Button *GridResetButton;
static GuiElement *TileGridPanel;
static Tilegrid *TileGrid;
static TextElement *SelectedHeader;
static GuiElement *SelectedTile;
static TextElement *SelectedModeHeader;
static TextElement *SelectedModeLabel;
static TextElement *MousePositionLabel;
static TextElement *LayerIndexLabel;
static TextInput *LayerIndex;
static Button *HideOtherLayers;


static const Font* pixelFont;
static const Font* Bold_pixelFont;

static Sprite getGuiSprite(std::string atlasid, int posx, int posy, int width, int height) {
	return Application::getInstance()->getTextureManager()->getSprite(atlasid, posx, posy, width, height);
}

inline void FileValueChanged(int index) {
	std::cout << index << std::endl;
}

inline void EditButtonUpdate(GuiElementEventContext ctx) {
	if (ctx.f_clickDown) {
		if (editPanel->isHidden()) editPanel->show();
		else editPanel->hide();
	}
}

inline void EditPanelUpdate(GuiElementEventContext ctx) {
	GuiElement *panel = ctx.element;
	if (ctx.f_deep_hovering && ctx.is_inside_window)
		panel->setRelativePosition(damp(panel->getRelativePosition(), Vector2f(-200, 0), 1.0f,
		                                Application::getInstance()->getDeltaTime()));
	else panel->setRelativePosition(damp(panel->getRelativePosition(), Vector2f(0, 0), 1.0f,
	                                     Application::getInstance()->getDeltaTime()));
}

inline void TileGridResetButtonUpdate(GuiElementEventContext ctx, Tilegrid *tilegrid) {
	if (ctx.f_clickDown) {
		tilegrid->setRelativePosition({0, 0});
		tilegrid->setScale({1,1});
	}
}

static bool active = false;

inline void ActiveHideOtherLayers(Editor *editor) {
	active = true;
	HideOtherLayers->getRectangleShape()->setFillColor(Color(170,17,14,255));
	editor->hideUnselected(true);
}

inline void DisableHideOtherLayers(Editor *editor) {
	active = false;
	HideOtherLayers->getRectangleShape()->setFillColor(Color(17,17,14,255));
	editor->hideUnselected(false);
}

inline GuiLayer *createEditorGui(Editor *editor) {
	pixelFont = Application::getInstance()->getFontManager()->getResource("PixelOperator8");
	Bold_pixelFont = Application::getInstance()->getFontManager()->getResource("PixelOperator8-Bold");
	GuiLayer *menu = new GuiLayer();

#pragma region File Dropdown
	fileButton = new Dropdown({72,24});
	fileButton->addText(pixelFont, "File");
	fileButton->getRectangleShape()->setFillColor(Color(17,17,14,255));
	fileButton->centerText();
	fileButton->getText()->setScale({0.5,0.5});
	fileButton->addEntry(pixelFont, "Open");
	fileButton->addEntry(pixelFont, "Save");
	fileButton->ValueChanged = &FileValueChanged;
	menu->addElement(fileButton, true);
#pragma endregion

#pragma region Edit Button
	editButton = new Button({72,24});
	editButton->addText(pixelFont, "Edit");
	editButton->getRectangleShape()->setFillColor(Color(17,17,14,255));
	editButton->centerText();
	editButton->getText()->setScale({0.5,0.5});
	editButton->Update = &EditButtonUpdate;
	editButton->setPosition({36 * 2, 0});
	menu->addElement(editButton, true);
#pragma endregion

#pragma region Edit Panel
	editPanel = new GuiElement({300, 300});
	editPanel->hide();
	editPanel->setOrigin({100, 0});
	editPanel->setAnchor(TopRight);
	editPanel->setRelativePosition({0, 0});
	editPanel->getRectangleShape()->setFillColor(Color(0, 0, 0, 200));
	editPanel->normalizeScaleRelativeToParent({0, 1});
	editPanel->Update = &EditPanelUpdate;
	editPanel->setBoundingBoxScale({1.5f, 1.0f});
	editPanel->setBoundingBoxOffset({-50.0f, 0.0f});
	menu->addElement(editPanel, false);
#pragma endregion

#pragma region Mode Label
	ModeLabel = new TextElement(Bold_pixelFont, "Mode");
	ModeLabel->setAnchor(AnchorType::TopCenter);
	ModeLabel->setOrigin(ModeLabel->getCenter());
	editPanel->append(ModeLabel);
	ModeLabel->setGlobalScale({0.30, 0.30});
	ModeLabel->setRelativePosition({0, 5});
#pragma endregion

#pragma region Draw Mode Button
	DrawModeButton = new Button(Vector2f(90,25));
	editPanel->append(DrawModeButton);
	DrawModeButton->setGlobalScale({1, 1});
	DrawModeButton->getRectangleShape()->setFillColor(Color(17, 17, 14, 255));
	DrawModeButton->addText(pixelFont, "Draw");
	DrawModeButton->getText()->setScale({0.5,0.5});
	DrawModeButton->centerText();
	DrawModeButton->setRelativePosition({7, 10});
	DrawModeButton->Update = [editor](GuiElementEventContext ctx) {
		if (ctx.f_clickUp) {
			editor->setState(DRAW);
			SelectedModeLabel->setString("Draw");
		}
	};
#pragma endregion

#pragma region Erase Mode Button
	EraseModeButton = new Button(Vector2f(90,25));
	editPanel->append(EraseModeButton);
	EraseModeButton->setGlobalScale({1, 1});
	EraseModeButton->getRectangleShape()->setFillColor(Color(17, 17, 14, 255));
	EraseModeButton->addText(pixelFont, "Erase");
	EraseModeButton->getText()->setScale({0.5,0.5});
	EraseModeButton->centerText();
	EraseModeButton->setRelativePosition({104, 10});
	EraseModeButton->Update = [editor](GuiElementEventContext ctx) {
		if (ctx.f_clickUp) {
			editor->setState(ERASE);
			SelectedModeLabel->setString("Erase");
		}
	};
#pragma endregion

#pragma region Select Mode Button
	SelectModeButton = new Button(Vector2f(90,25));
	editPanel->append(SelectModeButton);
	SelectModeButton->setGlobalScale({1, 1});
	SelectModeButton->getRectangleShape()->setFillColor(Color(17, 17, 14, 255));
	SelectModeButton->addText(pixelFont, "Select");
	SelectModeButton->getText()->setScale({0.5,0.5});
	SelectModeButton->centerText();
	SelectModeButton->setRelativePosition({201, 10});
	SelectModeButton->Update = [editor](GuiElementEventContext ctx) {
		if (ctx.f_clickUp) {
			editor->setState(SELECT);
			SelectedModeLabel->setString("Select");
		}
	};
#pragma endregion

#pragma region Tile Script Label
	ModeLabel = new TextElement(Bold_pixelFont, "Tile Script");
	ModeLabel->setAnchor(AnchorType::TopCenter);
	ModeLabel->setOrigin(ModeLabel->getCenter());
	editPanel->append(ModeLabel);
	ModeLabel->setGlobalScale({0.30, 0.30});
	ModeLabel->setRelativePosition({0, 32});
#pragma endregion

#pragma region Tile Script Panel
	TileScriptPanel = new TextInput(Vector2f(280,100),pixelFont, "write here...");
	editPanel->append(TileScriptPanel);
	TileScriptPanel->setAnchor(TopCenter);
	TileScriptPanel->SetOriginByAnchor(AnchorType::TopCenter);
	TileScriptPanel->setGlobalScale({1,1});
	TileScriptPanel->getRectangleShape()->setFillColor(Color(17, 17, 14, 255));
	TileScriptPanel->setRelativePosition({0, 37});

	TileScriptPanel->getTextElement()->setScale({0.5,0.5});
	TileScriptPanel->getTextElement()->setAnchor(TopLeft);
	TileScriptPanel->getTextElement()->SetOriginByAnchor(TopLeft);
	TileScriptPanel->getTextElement()->setRelativePosition({5, 5});
#pragma endregion

#pragma region Open Button
	OpenButton = new Button(Vector2f(90,25));
	editPanel->append(OpenButton);
	OpenButton->setGlobalScale({1, 1});
	OpenButton->getRectangleShape()->setFillColor(Color(17, 17, 14, 255));
	OpenButton->addText(pixelFont, "Open");
	OpenButton->getText()->setScale({0.5,0.5});
	OpenButton->centerText();
	OpenButton->setRelativePosition({10, 100});
	OpenButton->Update = [](GuiElementEventContext ctx) {
		if (ctx.f_clickUp) {
			if (auto* atlas = Application::getInstance()->getTextureManager()->getAtlasTexture(OpenPathLabel->getInput()))
				TileGrid->setTilemap(atlas, {16,16});
		}
	};
#pragma endregion

#pragma region Open Path Background
	/*OpenPathBackground = new GuiElement(Vector2f(180,25));
	OpenButton->append(OpenPathBackground);
	OpenPathBackground->setGlobalScale({1, 1});
	OpenPathBackground->getRectangleShape()->setFillColor(Color(17, 17, 14, 120));
	OpenPathBackground->setRelativePosition({100, 0});*/
#pragma endregion

#pragma region Open Path Label
	OpenPathLabel = new TextInput(Vector2f(350,50),pixelFont, "id...");
	OpenButton->append(OpenPathLabel);
	OpenPathLabel->getBackground()->setFillColor(Color(17, 17, 14, 120));
	OpenPathLabel->setGlobalScale({0.5, 0.5});
	OpenPathLabel->setAnchor(AnchorType::MiddleRight);
	OpenPathLabel->SetOriginByAnchor(AnchorType::MiddleLeft);
	OpenPathLabel->setRelativePosition({10,0});
	OpenPathLabel->HitEnter = []() {
		if (auto* atlas = Application::getInstance()->getTextureManager()->getAtlasTexture(OpenPathLabel->getInput()))
			TileGrid->setTilemap(atlas, {16,16});
	};

#pragma endregion

#pragma region Tile Grid Panel
	TileGridPanel = new GuiElement({300, 300});
	editPanel->append(TileGridPanel);
	TileGridPanel->getRectangleShape()->setFillColor(Color(0, 0, 0, 200));
	TileGridPanel->setGlobalScale({1, 1});
	TileGridPanel->setPosition({0, 120});
#pragma endregion

#pragma region Tile Grid
	TileGrid = new Tilegrid(
		Application::getInstance()->getTextureManager()->getAtlasTexture("tileset\\furnitures"), {16, 16});
	TileGridPanel->append(TileGrid);
	TileGrid->setGlobalScale({1, 1});
	TileGrid->SelectTile = [editor](IntRect r) {
		Sprite s = Sprite(*TileGrid->getTilemap(),r);
		SelectedTile->setSprite(s);
		editor->setSelectedTile(s);
	};
#pragma endregion

#pragma region Grid Reset Button
	GridResetButton = new Button({30, 30});
	TileGridPanel->append(GridResetButton);
	GridResetButton->setGlobalScale({0.75, 0.75});
	GridResetButton->getRectangleShape()->setFillColor(Color(170, 17, 14, 255));
	GridResetButton->addText(pixelFont, "R");
	GridResetButton->centerText();
	GridResetButton->getText()->setScale({0.75,0.75});
	GridResetButton->setAnchor(TopRight);
	GridResetButton->SetOriginByAnchor(AnchorType::TopRight);
	GridResetButton->setRelativePosition({-5, 5});
	GridResetButton->Update = [](GuiElementEventContext ctx) {TileGridResetButtonUpdate(ctx, TileGrid);};
#pragma endregion

#pragma region Selected Header
	SelectedHeader = new TextElement(pixelFont, "Selected:");
	editPanel->append(SelectedHeader);
	SelectedHeader->setGlobalScale({0.3,0.3});
	SelectedHeader->setAnchor(AnchorType::BottomLeft);
	SelectedHeader->setRelativePosition({3, -9});
#pragma endregion

#pragma region Selected Tile
	SelectedTile = new GuiElement({32, 32});
	SelectedHeader->append(SelectedTile);
	SelectedTile->setGlobalScale({0.5, 0.5});
	SelectedTile->setAnchor(AnchorType::MiddleRight);
	SelectedTile->SetOriginByAnchor(MiddleLeft);
	SelectedTile->setRelativePosition({12, 0});
#pragma endregion

#pragma region Selected Mode Header
	SelectedModeHeader = new TextElement(Bold_pixelFont, "Mode:");
	editPanel->append(SelectedModeHeader);
	SelectedModeHeader->setGlobalScale({0.3,0.3});
	SelectedModeHeader->setAnchor(AnchorType::BottomLeft);
	SelectedModeHeader->setRelativePosition({120, -9});
#pragma endregion

#pragma region Selected Mode Label
	SelectedModeLabel = new TextElement(pixelFont, "Draw");
	SelectedModeHeader->append(SelectedModeLabel);
	SelectedModeLabel->setGlobalScale({0.3,0.3});
	SelectedModeLabel->setAnchor(AnchorType::MiddleRight);
	SelectedModeLabel->SetOriginByAnchor(MiddleLeft);
	SelectedModeLabel->setRelativePosition({2, 0});
#pragma endregion

#pragma region Mouse Position Label
	MousePositionLabel = new TextElement(pixelFont, "X: 0 Y: 0");
	MousePositionLabel->setAnchor(AnchorType::BottomLeft);
	MousePositionLabel->setOrigin(MousePositionLabel->getPositionRelativeToAnchor(AnchorType::BottomLeft));
	MousePositionLabel->setRelativePosition({210, -5});
	MousePositionLabel->setGlobalScale({0.55f, 0.55f});
	MousePositionLabel->setFillColor(Color(255, 255, 255, 255));
	MousePositionLabel->Update = [](GuiElementEventContext ctx) {
		TextElement *t = static_cast<TextElement *>(ctx.element);
		t->setString(vec2tostring(ctx.mousePos));
	};
	menu->addElement(MousePositionLabel, false);
#pragma endregion

#pragma region Layer Index Label
	LayerIndexLabel = new TextElement(pixelFont, "Layer:");
	LayerIndexLabel->setAnchor(AnchorType::BottomLeft);
	LayerIndexLabel->SetOriginByAnchor(BottomLeft);
	LayerIndexLabel->setRelativePosition({0, -5});
	LayerIndexLabel->setScale({0.5, 0.5});
	menu->addElement(LayerIndexLabel, false);
#pragma endregion

#pragma region Layer Index
	LayerIndex = new TextInput(Vector2f(150,50),pixelFont, "0");
	LayerIndexLabel->append(LayerIndex);
	LayerIndex->setAnchor(AnchorType::MiddleRight);
	LayerIndex->SetOriginByAnchor(MiddleLeft);
	LayerIndex->getBackground()->setFillColor({17,17,14,255});
	LayerIndex->setRelativePosition({10, 0});
	LayerIndex->onlyNums = true;
	LayerIndex->TextChanged = [editor]() {
		DisableHideOtherLayers(editor);
		try {
			editor->setLayer(std::stoi(LayerIndex->getInput()));
		} catch (std::invalid_argument) {
			editor->setLayer(0);
		}

	};
#pragma endregion

#pragma region Hide Other Layers
	HideOtherLayers = new Button({40,40});
	LayerIndex->append(HideOtherLayers);
	HideOtherLayers->setAnchor(AnchorType::MiddleRight);
	HideOtherLayers->SetOriginByAnchor(MiddleLeft);
	HideOtherLayers->setRelativePosition({10, 0});
	HideOtherLayers->addText(pixelFont, "H", Color::White);
	HideOtherLayers->getRectangleShape()->setFillColor(Color(17,17,14,255));
	HideOtherLayers->centerText();
	HideOtherLayers->Update = [editor](GuiElementEventContext ctx) {
		if (ctx.f_clickUp) {
			if (active)
				DisableHideOtherLayers(editor);
			else
				ActiveHideOtherLayers(editor);
		}
	};
#pragma endregion
	return menu;
}


#endif
