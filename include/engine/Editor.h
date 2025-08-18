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
    void setSelectedTile(Sprite s);
    void click(Vector2f pos);
    void setLayer(int layer);
    void update(gui::GuiEventContext ctx, bool mouseOverGUI);
    void scroll(float mouse_wheel_delta, Vector2f mousePos, PixelPerfectRenderTarget *renderTarget);

private:
    std::optional<Tile> selectedTile;
    editorState state = DRAW;
    Level** level;
    int layerIndex = 0;
};



#endif //EDITOR_H
