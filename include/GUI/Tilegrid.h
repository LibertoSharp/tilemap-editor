#ifndef TILEGRID_H
#define TILEGRID_H
#include "Button.h"
#include "GuiElement.h"
#include "engine/Editor.h"

namespace gui {

class Tilegrid final : public GuiElement{
public:
	Tilegrid(const sf::Texture *textureAtlas, sf::Vector2u tileSize);
	~Tilegrid();
	void draw(RenderTarget &target, RenderStates states) const override;
	FloatRect getGlobalBounds();
	void update() override;
	std::function<void(IntRect r)> SelectTile = nullptr;
	void setTilemap(const sf::Texture *textureAtlas, sf::Vector2u tileSize);
	const Texture *getTilemap() const;
private:
	void ButtonUpdate(GuiElementEventContext ctx);

	float scrollSensitivity = 0.35f;
	Button *tileMap = nullptr;
	GuiElement *highlight = nullptr;
	Vector2u tileSize;
	bool dragging = false;
	Vector2f initialMousePos;
	GuiElement *element = nullptr;
	const sf::Texture *textureAtlas = nullptr;
};

} // gui

#endif //TILEGRID_H
