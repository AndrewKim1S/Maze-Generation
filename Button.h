#include <iostream>

#include <SFML/Graphics.hpp>
#include <cassert>

class Button {
		public:
				bool visible;
		
				Button();
				Button(int x, int y, sf::Vector2f s, std::string t);
				~Button();
				void render(sf::RenderTarget* target);
				bool clicked(sf::Vector2i mousePos);
		
		private:
				sf::Vector2f position;
				sf::Vector2f size;
				sf::RectangleShape shape;

				std::string label;
				sf::Font* font;
				sf::Text text;
};
