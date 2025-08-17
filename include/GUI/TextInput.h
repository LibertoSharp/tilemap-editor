#ifndef TEXTINPUT_H
#define TEXTINPUT_H
#include <iostream>

#include "Common.h"
#include "TextElement.h"

namespace gui {
	class TextInput final : public GuiElement {
	public:
		TextInput(Vector2f size, const Font *font, const string &placeholder) : GuiElement(background) {
			background = new RectangleShape(Vector2f(size.x, size.y));
			placeholderText = placeholder;
			activeGraphic = background;
			noFocusColor = Color(191,191, 191);

			text = new TextElement(font, placeholderText);
			this->append(text);
			text->setAnchor(MiddleLeft);
			text->SetOriginByAnchor(MiddleLeft);
			text->setRelativePosition({2,0});
			text->clickTransparent = true;
		}
		~TextInput() override;
		RectangleShape *getBackground();
		void SetDefaultColor(Color c);
		void update() override;
		string getInput();
		std::function<void()> HitEnter = nullptr;


	private:
		RectangleShape *background;
		TextElement *text;
		bool focus = false;
		string inputText = "";
		string placeholderText = "";
		Color defaultColor = Color::White;
		Color noFocusColor;
	};
} // gui

#endif //TEXTINPUT_H
