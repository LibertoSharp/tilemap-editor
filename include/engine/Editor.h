#ifndef EDITOR_H
#define EDITOR_H
#include "level/Level.h"
#include "level/Tile.h"

enum editorState {
    DRAW,
    ERASE,
    SELECT
};

class Editor {
public:
    Editor(Level **level);
    void update();
    void setState(editorState state);
    void setSelectedTile(Sprite s);
    void click(Vector2f pos);
private:
    std::optional<Tile> selectedTile;
    editorState state = DRAW;
    Level** level;
};



#endif //EDITOR_H
