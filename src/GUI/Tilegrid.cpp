#include "GUI/Tilegrid.h"

#include <cmath>

#include "engine/Application.h"

namespace gui {
	Tilegrid::Tilegrid(const sf::Texture *textureAtlas, sf::Vector2u tileSize): GuiElement(this)
	{
		Image textureImage = textureAtlas->copyToImage();
		this->clickTransparent = true;
		for (int y = 0; y < textureAtlas->getSize().y / tileSize.y; y++) {
			for (int x = 0; x < textureAtlas->getSize().x / tileSize.x; x++) {
				IntRect r = {{static_cast<int>(x*tileSize.x),static_cast<int>(y*tileSize.y)},Vector2<int>(tileSize)};
				Sprite s = Sprite(*textureAtlas, r);
				if (isEmptySprite(textureImage,r))
					continue;
				Button* tileButton = new Button(s);
				this->append(tileButton);
				tileButton->setRelativePosition({static_cast<float>(x*tileSize.x),static_cast<float>(y*tileSize.y)});
				tileButton->Update = [this](GuiElementEventContext ctx){this->ButtonUpdate(ctx);};
				tileButton->setShader(Application::getInstance()->getShaderManager()->getShader("tileButton"));
				tileButton->clickTransparent = true;
				tileButtons.push_back(tileButton);
			}
		}
	}

	Tilegrid::~Tilegrid() {
		for (auto tileButton: tileButtons) {
			delete tileButton;
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

	GuiElement* element = nullptr;
	FloatRect Tilegrid::getGlobalBounds() {
		if (!element) element = dynamic_cast<GuiElement*>(parent);
		if (element) {
			return element->getBoundingBox(element->activeGraphic);
		}
		return {};
	}

	bool dragging = false;
	Vector2f initialMousePos;
	void Tilegrid::update() {
		if (!element) element = dynamic_cast<GuiElement*>(parent);
		if (element && element->ctx.f_deep_hovering) {
			Vector2f s = this->getScale();
			s = {s.x + ctx.mouse_wheel_delta * scrollSensitivity, s.y + ctx.mouse_wheel_delta * scrollSensitivity};
			if (s.x > 0 && s.y > 0)
				this->setScale(s);
			if (element->ctx.f_clickDown) {
				initialMousePos = Vector2f(ctx.mousePos) - this->getGlobalPosition();
				dragging = true;
			}
		}

		if (ctx.f_globalclickup)
			dragging = false;
		if (dragging)
			this->setGlobalPosition(Vector2f(ctx.mousePos) - initialMousePos);

		GuiElement::update();
	}

	void Tilegrid::ButtonUpdate(GuiElementEventContext ctx) {
		static Vector2i initialMousePos;

		FloatRect bounds = this->transformRect(this->getGlobalBounds(), getParentTransform());
		Glsl::Vec4 globalrect = {bounds.position.x, bounds.position.y, bounds.size.x, bounds.size.y};
		ctx.element->getShader()->setUniform("maskRect", globalrect);
		ctx.element->getShader()->setUniform("uTime", Application::getInstance()->getTime());

		if (ctx.f_hovering && bounds.contains(Vector2<float>(ctx.mousePos))) {
			ctx.element->getShader()->setUniform("hovering", true);
			if (ctx.f_clickDown) {
				initialMousePos = ctx.mousePos;
			}
			if (ctx.f_clickUp && initialMousePos == ctx.mousePos) {
				cout << "megasbors" << endl;
			}
		} else
			ctx.element->getShader()->setUniform("hovering", false);
	}
} // gui