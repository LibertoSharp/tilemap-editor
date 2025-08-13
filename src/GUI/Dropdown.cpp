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
		entries.push_back(std::make_pair(s, hovered));
	}

	void Dropdown::showDropdown() {
		float y = this->getActiveSprite()->getGlobalBounds().size.y;
		int i = 0;
		for (std::pair<Sprite,Sprite> s: entries) {
			Button *btn = new Button(s.first);
			btn->hovered = s.second;
			btn->pressed = s.second;
			append(btn);
			btn->normalizeScaleRelativeToParent({1,1});
			btn->setAnchor(gui::TopLeft);
			btn->setRelativePosition({0,y});
			btn->Update = [this,i](gui::GuiElementEventContext ctx) {if (ctx.f_clickDown) {if (this->ValueChanged) this->ValueChanged(i); this->hideDropdown();}};
			y += btn->getActiveSprite()->getGlobalBounds().size.y;
			buttons.push_back(btn);
			i++;
		}
		dropped = true;
	}

	void Dropdown::hideDropdown() {
		for (auto btn: buttons) {
			btn->destroy();
		}
		buttons.clear();
		dropped = false;
	}
}