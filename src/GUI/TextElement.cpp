#include "GUI/TextElement.h"

namespace gui {
	void TextElement::setString(string str) {
		text.setString(str);
	}

	void TextElement::setFont(Font *font) {
		text.setFont(*font);
	}

	void TextElement::setFillColor(Color color) {
		text.setFillColor(color);
	}
}
