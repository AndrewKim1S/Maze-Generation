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
				bool visited;
				bool top;
				bool left;
				bool right;
				bool bottom;
				
				Cell();
				Cell(int x, int y, int length, int gridX, int gridY);
				~Cell();
				void setState(State s);
				void render(sf::RenderTarget* target);
				void removeWall(int wall);
				void reset();
				sf::Vector2f getGridPos();

		private:
				sf::Vector2f size;
				sf::Vector2f position;
				sf::Vector2f gridPosition;

				sf::RectangleShape topWall;
				sf::RectangleShape leftWall;
				sf::RectangleShape rightWall;
				sf::RectangleShape bottomWall;
				
				sf::RectangleShape TLcorner;
				sf::RectangleShape TRcorner;
				sf::RectangleShape BLcorner;
				sf::RectangleShape BRcorner;
				
				sf::RectangleShape shape;

				sf::Color wallColor = sf::Color::White;
				sf::Color cellColor = sf::Color(32, 32, 32);

				sf::Color cellBacktrackColor;
				sf::Color cellSelectedColor;
				
				sf::Color cellStartColor;
				sf::Color cellTargetColor;

				State state;


};
