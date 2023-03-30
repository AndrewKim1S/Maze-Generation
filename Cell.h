#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

enum class State{
		Start,
		Target,
		Path
};

class Cell{

		public:
				Cell();
				Cell(int x, int y, int length);
				~Cell();
				void setState(State s);
				void render(sf::RenderTarget* target);
				void removeWall(int wall);
				void reset();

		private:
				sf::Vector2f size;
				sf::Vector2f position;

				sf::RectangleShape topWall;
				sf::RectangleShape leftWall;
				sf::RectangleShape rightWall;
				sf::RectangleShape bottomWall;
				sf::RectangleShape shape;

				sf::Color wallColor = sf::Color::White;
				sf::Color cellColor = sf::Color(32, 32, 32);
				sf::Color cellBacktrackColor;
				sf::Color cellSelectedColor;

				State state;

				bool top;
				bool left;
				bool right;
				bool bottom;
};
