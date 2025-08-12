#include "GUI/Tilegrid.h"

namespace gui {
	Tilegrid::Tilegrid(const sf::Texture *textureAtlas, sf::Vector2u tileSize): GuiElement(this)
	{
		for (int y = 0; y < textureAtlas->getSize().y / tileSize.y; y++) {
			for (int x = 0; x < textureAtlas->getSize().x / tileSize.x; x++) {
				IntRect r = {{static_cast<int>(x*tileSize.x),static_cast<int>(y*tileSize.y)},Vector2<int>(tileSize)};
				Button* tileButton = new Button(Sprite(*textureAtlas, r));
				this->append(tileButton);
				tileButton->setRelativePosition({static_cast<float>(x*tileSize.x),static_cast<float>(y*tileSize.y)});
				tileButton->Update = [this](GuiElementEventContext ctx){this->ButtonUpdate(ctx);};
				tileButtons.push_back(tileButton);
			}
		}
	}

	void Tilegrid::draw(RenderTarget &target, RenderStates states) const {
		if (isHidden()) return;

		states.transform *= getTransform();

		auto childs = getChildrens();
		for (auto child: childs) {
			if (child)
				target.draw(*child, states);
		}
	}

	void Tilegrid::ButtonUpdate(GuiElementEventContext ctx) {
		//highlight
	}
} // gui