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
private:
	void ButtonUpdate(GuiElementEventContext ctx);

	float scrollSensitivity = 0.35f;
	Button *tileMap = nullptr;
	GuiElement *highlight = nullptr;
	Vector2u tileSize;
};

} // gui

#endif //TILEGRID_H
