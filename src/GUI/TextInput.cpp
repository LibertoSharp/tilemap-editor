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
	if (ctx.f_globalclickdown)
		focus = false;
	if (ctx.f_clickUp) {
		focus = true;
	}
	text->setFillColor(noFocusColor);
	if (focus) {
		text->setFillColor(defaultColor);
		if (ctx.textEntered >= 32 && ctx.textEntered < 127)
			inputText += ctx.textEntered;
		if (ctx.keyPressed == Keyboard::Key::Backspace)
			inputText = inputText.substr(0, inputText.length() - 1);
		if (ctx.keyPressed == Keyboard::Key::Enter && HitEnter)
			HitEnter();
	}

	if (inputText.empty())
		text->setString(placeholderText);
	else {
		text->setString(inputText);
		if (text->transformRect( text->getBoundingBox(text->activeGraphic),text->getTransform()).size.x > this->getBoundingBox(activeGraphic).size.x) {
			inputText = inputText.substr(0, inputText.length() - 1);
			text->setString(inputText);
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
