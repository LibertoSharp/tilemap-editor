#include "engine/Editor.h"

#include <iostream>

#include "engine/Application.h"

Editor::Editor(Level **level) {
	this->level = level;
}

void Editor::setState(editorState state) {
	this->state = state;
}

void Editor::setSelectedTile(Sprite s) {
	selectedTile = Tile(s);
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

void Editor::update(gui::GuiEventContext ctx) {
	PixelPerfectRenderTarget *renderTarget = Application::getInstance()->getRenderTarget();
	if (ctx.f_clickDown)
		click({ctx.mousePos.x / (renderTarget->getZoom()),ctx.mousePos.y / (renderTarget->getZoom())});

	//scroll(ctx.mouse_wheel_delta, Vector2f(ctx.mousePos));
}

void Editor::scroll(float mouse_wheel_delta, Vector2f mousePos) {
	Vector2f oldScale = (**level).getScale();
	Vector2f newScale = {
		oldScale.x + mouse_wheel_delta,
		oldScale.y + mouse_wheel_delta
	};

	if (newScale.x > 0 && newScale.y > 0) {
		Vector2f cursor = Vector2f(mousePos);

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
