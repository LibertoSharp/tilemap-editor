#include "GUI/Tilegrid.h"

#include <cmath>

#include "engine/Application.h"

namespace gui {
	Tilegrid::Tilegrid(const string atlasID, sf::Vector2u tileSize): GuiElement(this), tileSize(tileSize) {
		this->clickTransparent = true;

		highlight = new GuiElement(Vector2f(tileSize));
		highlight->setRelativePosition({0, 0});
		highlight->setShader(Application::getInstance()->getShaderManager()->getShader("highlight"));
		highlight->clickTransparent = true;
		this->append(highlight);

		setTilemap(atlasID, tileSize);
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

	FloatRect Tilegrid::getGlobalBounds() {
		if (!element) element = dynamic_cast<GuiElement *>(parent);
		if (element) {
			return element->getBoundingBox(element->activeGraphic);
		}
		return {};
	}

	void Tilegrid::update() {
		if (!element) element = dynamic_cast<GuiElement *>(parent);
		if (element && element->ctx.f_deep_hovering && !dragging) {
			if (element->ctx.f_wheelClick) {
				initialMousePos = Vector2f(ctx.mousePos) - this->getGlobalPosition();
				dragging = true;
			}
			Vector2f oldScale = this->getScale();
			Vector2f newScale = {
				oldScale.x + ctx.mouse_wheel_delta * scrollSensitivity,
				oldScale.y + ctx.mouse_wheel_delta * scrollSensitivity
			};

			if (newScale.x > 0 && newScale.y > 0) {
				Vector2f cursor = Vector2f(ctx.mousePos);

				Vector2f oldPos = this->getGlobalPosition();

				Vector2f factor = {
					newScale.x / oldScale.x,
					newScale.y / oldScale.y
				};

				Vector2f newPos = {
					cursor.x - (cursor.x - oldPos.x) * factor.x,
					cursor.y - (cursor.y - oldPos.y) * factor.y
				};

				this->setScale(newScale);
				this->setGlobalPosition(newPos);
			}
		}

		if (ctx.f_globalWheelUp)
			dragging = false;
		if (dragging)
			this->setGlobalPosition(Vector2f(ctx.mousePos) - initialMousePos);

		GuiElement::update();
	}

	void Tilegrid::setTilemap(const string atlasID, sf::Vector2u tileSize) {
		const Texture* t = Application::getInstance()->getTextureManager()->getAtlasTexture(atlasID);
		if (!t) return;
		this->textureAtlas = t;
		this->atlasID = atlasID;
		this->tileSize = tileSize;
		if (tileMap)
			tileMap->destroy();

		IntRect rect = {{0, 0}, Vector2<int>(textureAtlas->getSize())};
		Sprite s = Sprite(*textureAtlas, rect);
		tileMap = new Button(s);
		this->append(tileMap);
		tileMap->setRelativePosition({0, 0});
		tileMap->Update = [this](GuiElementEventContext ctx) { this->ButtonUpdate(ctx); };
		tileMap->setShader(Application::getInstance()->getShaderManager()->getShader("tileButton"));
		tileMap->clickTransparent = true;
		highlight->goFront();
	}

	const Texture * Tilegrid::getTilemap() const {
		return textureAtlas;
	}

	std::string Tilegrid::getTilemapID() const {
		return atlasID;
	}

	void Tilegrid::ButtonUpdate(GuiElementEventContext ctx) {
		FloatRect bounds = this->transformRect(this->getGlobalBounds(), getParentTransform());
		Glsl::Vec4 globalrect = {bounds.position.x, bounds.position.y, bounds.size.x, bounds.size.y};
		ctx.element->getShader()->setUniform("maskRect", globalrect);
		highlight->getShader()->setUniform("maskRect", globalrect);
		if (ctx.f_hovering && bounds.contains(Vector2<float>(ctx.mousePos))) {
			highlight->getShader()->setUniform("uTime", Application::getInstance()->getTime());
			highlight->getShader()->setUniform("hovering", true);
			Vector2i relativeMousePos = (ctx.mousePos - Vector2i(this->getGlobalPosition()));
			relativeMousePos = Vector2i(relativeMousePos.x / this->getGlobalScale().x, relativeMousePos.y / this->getGlobalScale().y);
			highlight->setPosition(Vector2f((relativeMousePos.x/tileSize.x)*tileSize.x,(relativeMousePos.y/tileSize.y)*tileSize.y));
			if (ctx.f_clickUp) {
				IntRect r;
				r.position = Vector2i((relativeMousePos.x/tileSize.x)*tileSize.x,(relativeMousePos.y/tileSize.y)*tileSize.y);
				r.size = Vector2i(tileSize);
				SelectTile(r);
			}
		} else
			highlight->getShader()->setUniform("hovering", false);
	}
} // gui
