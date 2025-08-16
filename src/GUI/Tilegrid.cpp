#include "GUI/Tilegrid.h"

#include <cmath>

#include "engine/Application.h"

namespace gui {
	Tilegrid::Tilegrid(const sf::Texture *textureAtlas, sf::Vector2u tileSize): GuiElement(this), tileSize(tileSize) {
		this->clickTransparent = true;
		IntRect rect = {{0, 0}, Vector2<int>(textureAtlas->getSize())};
		Sprite s = Sprite(*textureAtlas, rect);
		tileMap = new Button(s);
		this->append(tileMap);
		tileMap->setRelativePosition({0, 0});
		tileMap->Update = [this](GuiElementEventContext ctx) { this->ButtonUpdate(ctx); };
		tileMap->setShader(Application::getInstance()->getShaderManager()->getShader("tileButton"));
		tileMap->clickTransparent = true;

		highlight = new GuiElement(Vector2f(tileSize));
		highlight->setRelativePosition({0, 0});
		highlight->setShader(Application::getInstance()->getShaderManager()->getShader("highlight"));
		highlight->clickTransparent = true;
		this->append(highlight);
	}

	Tilegrid::~Tilegrid() {
		delete tileMap;
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

	GuiElement *element = nullptr;

	FloatRect Tilegrid::getGlobalBounds() {
		if (!element) element = dynamic_cast<GuiElement *>(parent);
		if (element) {
			return element->getBoundingBox(element->activeGraphic);
		}
		return {};
	}

	bool dragging = false;
	Vector2f initialMousePos;

	void Tilegrid::update() {
		if (!element) element = dynamic_cast<GuiElement *>(parent);
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
		highlight->getShader()->setUniform("maskRect", globalrect);
		if (ctx.f_hovering && bounds.contains(Vector2<float>(ctx.mousePos))) {
			highlight->getShader()->setUniform("uTime", Application::getInstance()->getTime());
			highlight->getShader()->setUniform("hovering", true);
			Vector2i relativeMousePos = (ctx.mousePos - Vector2i(this->getGlobalPosition()));
			relativeMousePos = Vector2i(relativeMousePos.x / this->getGlobalScale().x, relativeMousePos.y / this->getGlobalScale().y);
			highlight->setPosition(Vector2f((relativeMousePos.x/16)*16,(relativeMousePos.y/16)*16));
			if (ctx.f_clickDown) {
				initialMousePos = ctx.mousePos;
			}
			if (ctx.f_clickUp && initialMousePos == ctx.mousePos) {
				cout << "megasbors" << endl;
			}
		} else
			highlight->getShader()->setUniform("hovering", false);
	}
} // gui
