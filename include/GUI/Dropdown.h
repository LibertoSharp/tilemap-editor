#ifndef DROPDOWN_H
#define DROPDOWN_H
#include "Button.h"

using namespace sf;
namespace gui {
	class Dropdown final : public gui::Button {
	public:
		explicit Dropdown(const sf::Sprite &sprite) : Button(sprite) {entries.reserve(3);}
		explicit Dropdown(Vector2f size) : Button(size) {entries.reserve(3); this->size = size;}
		void update() override;
		void addEntry(Sprite s,Sprite hovered);
		void addEntry(const Font *font, std::string text);

		std::function<void(int)> ValueChanged = nullptr;
	private:
		void showDropdown();
		void hideDropdown();

		std::vector<Button*> entries;
		bool dropped = false;
		Vector2f size;
	};
}
#endif //DROPDOWN_H
