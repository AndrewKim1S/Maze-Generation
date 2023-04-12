#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cassert>
#include "Cell.h"
#include "DepthFirst.h"
#include "HuntKill.h"
#include "Prims.h"
#include "Button.h"
#include "Menu.h"


class Application {
		
		// State of application
		enum State {
				Idle,
				Generate,
				Solve
		};

		// State of algorithm
		enum AlgorithmState {
				None,
				IterativeDFS,
				HuntkillAlgo,
				PrimsAlgo,
				KruskallsAlgo
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

				// Maze generation Algorithm functions
				void generateMazeDFS();
				void generateMazeHK();
				void generateMazePrim();

		private:
				// sfml enteties
				sf::RenderWindow* window;
				sf::Event event;
				sf::Clock clock;

				// States
				State appState;
				AlgorithmState algState;

				// Buttons & UI
				Button generateMazeDFSButton;
				Button generateMazeHKButton;
				Button generateMazePrimButton;
				Button restartMazeButton;
				Menu algorithmMenu;

				// Maze
				std::vector<std::vector<Cell>> grid;
				
				// Maze generation Algorithms
				DepthFirst dfsAlgorithm;
				HuntKill hkAlgorithm;
				Prims pmAlgorithm;

				// application settings
				int width;
				int height;

				int numCellWidth;
				int numCellHeight;

				// default size 50
				// 100 for testing
				int cellSize = 50;

				bool HudVisibility;
};
