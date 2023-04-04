#include "Menu.h"

Menu::Menu() {

}

Menu::Menu(int x, int y, sf::Vector2f s, std::string t) {
		position.x = x;
		position.y = y;
		size = s;
		label = t;

		displayButtons = false;

		font = new sf::Font();
		assert(font->loadFromFile("util/PlatNomor-eZ2dm.otf"));

		text = sf::Text();
		text.setFont(*font);
		text.setCharacterSize(16);
		text.setFillColor(sf::Color::Black);
		text.setString(label);
		text.setPosition(position.x + size.x/15, position.y + size.y/13);

		shape = sf::RectangleShape();
		shape.setSize(size);
		shape.setPosition(position.x, position.y);
		shape.setFillColor(sf::Color::White);
		shape.setOutlineColor(sf::Color(32, 32, 32));
		shape.setOutlineThickness(5);
}

Menu::~Menu() {
}

void Menu::render(sf::RenderTarget* target) {
		target->draw(shape);
		target->draw(text);
		if(displayButtons) {
				for(size_t i = 0; i < buttons.size(); i++) {
						buttons[i].render(target);
				}
		}
}

bool Menu::clicked(sf::Vector2i mousePos) {
		sf::FloatRect boundary = shape.getGlobalBounds();
		if(boundary.contains(mousePos.x, mousePos.y)) {
				displayButtons = !displayButtons;
				return true;
		}
		return false;
}

void Menu::addButton(Button& b) {
		buttons.push_back(b);
}
