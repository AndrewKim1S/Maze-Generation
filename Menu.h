#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <vector>
#include <cassert>
#include "Button.h"

class Menu {
		public:
				Menu();
				Menu(int x, int y, sf::Vector2f s, std::string t);
				~Menu();
				void render(sf::RenderTarget* target);
				bool clicked(sf::Vector2i mousePos);
				void addButton(Button& b);
		
		private:
				std::vector<Button> buttons;
				
				sf::Vector2f position;
				sf::Vector2f size;
				sf::RectangleShape shape;

				std::string label;
				sf::Font* font;
				sf::Text text;

				bool displayButtons;
};
