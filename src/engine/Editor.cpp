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
		(*level)->getGrid()->setTile(pos.x, pos.y, selectedTile.value());
}
