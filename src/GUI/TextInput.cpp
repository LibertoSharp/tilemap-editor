#include "GUI/TextInput.h"

gui::TextInput::~TextInput() {
	delete background;
	delete text;
	GuiElement::~GuiElement();
}

sf::RectangleShape * gui::TextInput::getBackground() {
	return background;
}

void gui::TextInput::SetDefaultColor(Color c) {
	defaultColor = c;
	noFocusColor = {static_cast<unsigned char>(c.r * 0.75), static_cast<unsigned char>(c.g * 0.75), static_cast<unsigned char>(c.b * 0.75), c.a};
	text->setFillColor(c);
}

void gui::TextInput::update() {
	FloatRect bounds = this->transformRect(background->getGlobalBounds(), getGlobalTransform());
	Glsl::Vec4 globalrect = {bounds.position.x, bounds.position.y, bounds.size.x, bounds.size.y};
	text->getShader()->setUniform("maskRect", globalrect);

	if (ctx.f_globalclickdown)
		focus = false;
	if (ctx.f_clickUp) {
		focus = true;
	}
	text->setFillColor(noFocusColor);
	if (focus) {
		text->setFillColor(defaultColor);
		if (ctx.textEntered >= 32 && ctx.textEntered < 127) {
			if ((onlyNums && ((ctx.textEntered >= 48 && ctx.textEntered < 58) || (ctx.textEntered == 45 && inputText.empty()))) || !onlyNums) {
				inputText += ctx.textEntered;
				if (TextChanged)
					TextChanged();
			}
		}
		if (ctx.keyPressed == Keyboard::Key::Backspace) {
			inputText = inputText.substr(0, inputText.length() - 1);
			if (TextChanged)
				TextChanged();
		}
		if (ctx.keyPressed == Keyboard::Key::Enter && HitEnter)
			HitEnter();
	}

	if (inputText.empty())
		text->setString(placeholderText);
	else {
		text->setString(inputText);
		if (text->transformRect( text->getBoundingBox(text->activeGraphic),text->getTransform()).size.x > this->getBoundingBox(activeGraphic).size.x) {

			if (multiline) {
				text->setAnchor(TopRight);
				text->SetOriginByAnchor(TopRight);
				text->setRelativePosition({5,5});
			}
			else {
				text->setAnchor(MiddleRight);
				text->SetOriginByAnchor(MiddleRight);
				text->setRelativePosition({0,0});
			}
		}
		else {
			if (multiline) {
				text->setAnchor(TopLeft);
				text->SetOriginByAnchor(TopLeft);
				text->setRelativePosition({5,5});
			}
			else {
				text->setAnchor(MiddleLeft);
				text->SetOriginByAnchor(MiddleLeft);
				text->setRelativePosition({0,0});
			}
		}
	}

	GuiElement::update();
}

gui::TextElement * gui::TextInput::getTextElement() {
	return text;
}

string gui::TextInput::getInput() {
	return inputText;
}
