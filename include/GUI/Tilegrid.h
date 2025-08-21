#ifndef TILEGRID_H
#define TILEGRID_H
#include "Button.h"
#include "GuiElement.h"
#include "engine/Editor.h"

namespace gui {

class Tilegrid final : public GuiElement{
public:
	Tilegrid(const std::string atlasID, sf::Vector2u tileSize);
	~Tilegrid();

	void setSize(sf::Vector2u tileSize);

	void draw(RenderTarget &target, RenderStates states) const override;
	FloatRect getGlobalBounds();
	void update() override;
	std::function<void(IntRect r)> SelectTile = nullptr;
	void setTilemap(std::string atlasID, sf::Vector2u tileSize);
	const Texture *getTilemap() const;
	std::string getTilemapID() const;
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
	std::string atlasID;
};

} // gui

#endif //TILEGRID_H
