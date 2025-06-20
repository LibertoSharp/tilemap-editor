#ifndef EDITOR_H
#define EDITOR_H
#include "level/Tile.h"

enum editorState {
    TILE_EDITING,
    INFO_EDITING
};
class Editor {
private:
    Tile selectedTile;
    editorState state = TILE_EDITING;
};



#endif //EDITOR_H
