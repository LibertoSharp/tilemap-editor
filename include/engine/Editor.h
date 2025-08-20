#ifndef EDITOR_H
#define EDITOR_H
#include "graphics/BackgroundGrid.h"
#include "graphics/PixelPerfectRenderTarget.h"
#include "GUI/GuiLayer.h"
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
    void setState(editorState state);
    void setSelectedTile(std::string atlasID, IntRect r);
    void click(Vector2f pos);
    void setLayer(int layer);
    void update(gui::GuiEventContext ctx, bool mouseOverGUI);
    void scroll(float mouse_wheel_delta, Vector2f mousePos, PixelPerfectRenderTarget *renderTarget);
    void hideUnselected(bool active);
    void saveLevel();

private:
    std::optional<Tile> selectedTile;
    editorState state = DRAW;
    Level** level;
    int layerIndex = 0;
};

inline void Editor::saveLevel() {
    (**level).saveFile("C:\\Users\\lucav\\Desktop\\out.bin");
}


#endif //EDITOR_H
