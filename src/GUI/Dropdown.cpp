#include "GUI/Dropdown.h"

#include <iostream>
namespace gui {
	void Dropdown::update() {
		if ((ctx.f_clickUp || ctx.f_globalclickup) && dropped)
				hideDropdown();
		else if (ctx.f_clickUp && !dropped)
				showDropdown();
		Button::update();
	}

	void Dropdown::addEntry(Sprite s, Sprite hovered) {
		int index = entries.size();
		Button *btn = new Button(s);
		btn->hovered = hovered;
		btn->pressed = hovered;
		if (index == 0) this->append(btn);
		else (*(entries.end()-1))->append(btn);
		btn->setAnchor(AnchorType::BottomLeft);
		btn->setRelativePosition({0,0});
		btn->Update = [this,index](gui::GuiElementEventContext ctx) {if (ctx.f_clickDown) {if (this->ValueChanged) this->ValueChanged(index); this->hideDropdown();}};
		btn->hide();
		entries.push_back(btn);
	}

	void Dropdown::addEntry(const Font *font, std::string text) {
		int index = entries.size();
		Button *btn = new Button(size);
		btn->addText(font,text);
		btn->centerText();
		btn->getText()->setScale(this->getText()->getScale());
		btn->getRectangleShape()->setFillColor(this->getRectangleShape()->getFillColor());
		if (index == 0) this->append(btn);
		else (*(entries.end()-1))->append(btn);
		btn->setAnchor(AnchorType::BottomLeft);
		btn->setRelativePosition({0,0});
		btn->Update = [this,index](gui::GuiElementEventContext ctx) {if (ctx.f_clickDown) {if (this->ValueChanged) this->ValueChanged(index); this->hideDropdown();}};
		btn->hide();
		entries.push_back(btn);
	}

	void Dropdown::showDropdown() {
		for (Button *s: entries) {
			s->show();
		}
		dropped = true;
	}

	void Dropdown::hideDropdown() {
		for (Button *s: entries) {
			s->hide();
		}
		dropped = false;
	}
}