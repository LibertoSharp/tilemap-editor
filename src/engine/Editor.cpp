#include "engine/Editor.h"

#include <iostream>

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
