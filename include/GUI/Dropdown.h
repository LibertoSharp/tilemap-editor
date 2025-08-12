#ifndef DROPDOWN_H
#define DROPDOWN_H
#include "Button.h"

using namespace sf;
namespace gui {
	class Dropdown final : public gui::Button {
	public:
		explicit Dropdown(const sf::Sprite &sprite) : Button(sprite) {entries.reserve(3);}
		void update() override;
		void addEntry(Sprite s,Sprite hovered);

		std::function<void(int)> ValueChanged = nullptr;
	private:
		void showDropdown();
		void hideDropdown();

		std::vector<std::pair<Sprite,Sprite>> entries;
		std::vector<Button*> buttons;
		bool dropped = false;
	};
}
#endif //DROPDOWN_H
