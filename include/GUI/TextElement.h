#ifndef TEXT_H
#define TEXT_H
#include "GuiElement.h"

using namespace std;
namespace gui {

class TextElement final : public GuiElement{
	public:
	explicit TextElement(const Font *font, string str) : text(*font,str), GuiElement(&text) {}
	void setString(string str);
	void setFont(Font *font);
	void setFillColor(Color color);

private:
	sf::Text text;
};

} // gui

#endif //TEXT_H
