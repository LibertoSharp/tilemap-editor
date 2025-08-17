#ifndef TILEGRID_H
#define TILEGRID_H
#include "Button.h"
#include "GuiElement.h"

namespace gui {

class Tilegrid final : public GuiElement{
public:
	Tilegrid(const sf::Texture *textureAtlas, sf::Vector2u tileSize);
	~Tilegrid();
	void draw(RenderTarget &target, RenderStates states) const override;
	FloatRect getGlobalBounds();
	void update() override;
	void setTilemap(const sf::Texture *textureAtlas, sf::Vector2u tileSize);
private:
	void ButtonUpdate(GuiElementEventContext ctx);

	float scrollSensitivity = 0.35f;
	Button *tileMap = nullptr;
	GuiElement *highlight = nullptr;
	Vector2u tileSize;
	bool dragging = false;
	Vector2f initialMousePos;
	GuiElement *element = nullptr;
};

} // gui

#endif //TILEGRID_H
