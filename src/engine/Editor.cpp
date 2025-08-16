#include "engine/Editor.h"

Editor::Editor(Level **level) {
	this->level = level;
}

void Editor::setState(editorState state) {
	this->state = state;
}
