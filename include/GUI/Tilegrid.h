#ifndef TILEGRID_H
#define TILEGRID_H
#include "Button.h"
#include "GuiElement.h"

namespace gui {

class Tilegrid final : public GuiElement{
public:
	Tilegrid(const sf::Texture *textureAtlas, sf::Vector2u tileSize);
	void draw(RenderTarget &target, RenderStates states) const override;

private:
	void ButtonUpdate(GuiElementEventContext ctx);
	std::vector<Button*> tileButtons;
};

} // gui

#endif //TILEGRID_H
