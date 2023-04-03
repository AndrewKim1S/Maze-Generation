#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Cell.h"
#include "DepthFirst.h"


class Application {
		
		enum State {
				Idle,
				Generate,
				Solve
		};

		public:
				Application();
				Application(int w, int h);
				~Application();
				void render();
				void run();
				void pollEvents();
				void update();
				bool isRunning();
				void createGrid();
				void generateMaze();

		private:
				sf::RenderWindow* window;
				sf::Event event;
				sf::Clock clock;

				State appState;

				Cell test;
				std::vector<std::vector<Cell>> grid;
				DepthFirst dfsAlgorithm;
				int width;
				int height;

				int numCellWidth;
				int numCellHeight;

				// default size 50;
				int cellSize = 50;
};
