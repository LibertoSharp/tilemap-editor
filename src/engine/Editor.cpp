#include "engine/Editor.h"

#include <iostream>

#include "engine/Application.h"

Editor::Editor(Level **level) {
	this->level = level;
}

void Editor::setState(editorState state) {
	this->state = state;
}

void Editor::setSelectedTile(string atlasID, IntRect r) {
	selectedTile = Tile(r, atlasID);
}

void Editor::click(Vector2f pos) {
	if (selectedTile.has_value() && state == DRAW)
		(*level)->getGrid(layerIndex)->setTile(pos.x / (*level)->getTileSize(), pos.y / (*level)->getTileSize(), selectedTile.value());
	if (state == ERASE)
		(*level)->getGrid(layerIndex)->setTile(pos.x / (*level)->getTileSize(), pos.y / (*level)->getTileSize(), std::nullopt);
}

void Editor::setLayer(int layer) {
	layerIndex = layer;
}

void Editor::update(gui::GuiEventContext ctx, bool mouseOverGUI) {
	static bool startDrag = false;
	static Vector2i initialMousePos;
	static Vector2f initialDragPos;
	PixelPerfectRenderTarget *renderTarget = Application::getInstance()->getRenderTarget();
	Vector2f clickPosition = {(ctx.mousePos.x / renderTarget->getZoom()) ,ctx.mousePos.y / (renderTarget->getZoom())};

	if (!mouseOverGUI) return;

	if (ctx.f_mouseDown)
		click({(clickPosition.x - (**level).getPosition().x) / (**level).getScale().x, (clickPosition.y - (**level).getPosition().y) / (**level).getScale().y});

	scroll(ctx.mouse_wheel_delta, Vector2f(ctx.mousePos), renderTarget);
	if (ctx.f_wheelClick) {
		initialMousePos = Vector2i(clickPosition);
		initialDragPos = (**level).getPosition();
		startDrag = true;
	}
	if (ctx.f_wheelDown && startDrag) {
		(**level).setPosition({initialDragPos.x + clickPosition.x - initialMousePos.x,initialDragPos.y + clickPosition.y - initialMousePos.y});
	}
	if (ctx.f_wheelUp)
		startDrag = false;

}

void Editor::scroll(float mouse_wheel_delta, Vector2f mousePos,PixelPerfectRenderTarget *renderTarget) {
	Vector2f oldScale = (**level).getScale();
	Vector2f newScale = {
		oldScale.x + mouse_wheel_delta * 0.1f,
		oldScale.y + mouse_wheel_delta * 0.1f
	};

	if (newScale.x > 0 && newScale.y > 0) {
		Vector2f cursor = Vector2f(mousePos.x/renderTarget->getZoom(),mousePos.y/renderTarget->getZoom());

		Vector2f oldPos = (**level).getPosition();

		Vector2f factor = {
			newScale.x / oldScale.x,
			newScale.y / oldScale.y
		};

		Vector2f newPos = {
			cursor.x - (cursor.x - oldPos.x) * factor.x,
			cursor.y - (cursor.y - oldPos.y) * factor.y
		};

		(**level).setScale(newScale);
		(**level).setPosition(newPos);
	}
}

void Editor::hideUnselected(bool active) {
	(*level)->ShowOnly(layerIndex);
	(*level)->f_showOnly = active;
}


void Editor::saveLevel(std::string filename) const {
	(**level).saveFile(filename);
}

void Editor::loadLevel(std::string filename, gui::Tilegrid *tileGrid) {
	try {
		(**level).loadFile(filename, tileGrid);
		selectedTile = std::nullopt;
	} catch (...) {
		
	}


}
