#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cassert>
#include "Cell.h"
#include "DepthFirst.h"
#include "HuntKill.h"
#include "Button.h"
#include "Menu.h"


class Application {
		
		enum State {
				Idle,
				Generate,
				Solve
		};

		enum AlgorithmState {
				None,
				IterativeDFS,
				HuntkillAlgo,
				Prims,
				Kruskalls
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
				void createUI();
				void generateMazeDFS();
				void generateMazeHK();

		private:
				sf::RenderWindow* window;
				sf::Event event;
				sf::Clock clock;

				State appState;
				AlgorithmState algState;

				Button generateMazeDFSButton;
				Button generateMazeHKButton;
				Button restartMazeButton;
				Menu algorithmMenu;

				std::vector<std::vector<Cell>> grid;
				
				DepthFirst dfsAlgorithm;
				HuntKill hkAlgorithm;

				int width;
				int height;

				int numCellWidth;
				int numCellHeight;

				// default size 50;
				int cellSize = 50;

				bool HudVisibility;
};
