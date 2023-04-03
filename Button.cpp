#include "Button.h"


Button::Button() {

}

Button::Button(int x, int y, sf::Vector2f s, std::string t) {
		position.x = x;
		position.y = y;
		size = s;
		visible = true;
		label = t;
		
		font = new sf::Font();
		assert(font->loadFromFile("util/PlatNomor-eZ2dm.otf"));

		text = sf::Text();
		text.setFont(*font);
		text.setCharacterSize(16);
		text.setFillColor(sf::Color::Black);
		text.setString(label);
		text.setPosition(position.x + size.x/15, position.y + size.y/13.5);

		shape = sf::RectangleShape();
		shape.setSize(size);
		shape.setPosition(position.x, position.y);
		shape.setFillColor(sf::Color::White);
		shape.setOutlineThickness(4);
		shape.setOutlineColor(sf::Color::Black);
}

Button::~Button() {

}

void Button::render(sf::RenderTarget* target) {
		target->draw(shape);
		target->draw(text);
}

bool Button::clicked(sf::Vector2i mousePos) {
		sf::FloatRect boundary = shape.getGlobalBounds();
		return boundary.contains(mousePos.x, mousePos.y);
}
