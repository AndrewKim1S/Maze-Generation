#include "Application.h"


Application::Application() {

}

Application::Application(int w, int h) {
		window = new sf::RenderWindow(sf::VideoMode(w, h), "Maze Generation");
		window->setPosition(sf::Vector2i(200, 75));
		width = w;
		height = h;

		// 
		appState = State::Idle;
		algState = AlgorithmState::None;

		numCellWidth = width/cellSize;
		numCellHeight = height/cellSize;

		grid.resize(static_cast<size_t>(numCellWidth));
		for(size_t i = 0; i < grid.size(); i++) {
				grid[i].resize(static_cast<size_t>(numCellHeight));
		}

		createGrid();
		createUI();

		hkAlgorithm = HuntKill(grid);
		dfsAlgorithm = DepthFirst(grid);

		HudVisibility = true;
}

Application::~Application() {
		delete window;
}

void Application::render() {
		window->clear(sf::Color(44, 105, 141));
		for(size_t i = 0; i < grid.size(); i++) {
				for(size_t k = 0; k < grid[i].size(); k++) {
						grid[i][k].render(window);
				}
		}
		if(HudVisibility) {
				algorithmMenu.render(window);
				restartMazeButton.render(window);
		}
		window->display();
}

void Application::run() {
		update();
		render();
		pollEvents();
}

void Application::pollEvents() {
		while(window->pollEvent(event)) {
				switch(event.type) {

						// Window close event
						case sf::Event::Closed:
								window->close();
								break;

						// Key press event 
						case sf::Event::KeyPressed:
								// escape close window
								if(event.key.code == sf::Keyboard::Escape) {
										window->close();
								}	
								// Key binding D generate DFS maze
								else if(event.key.code == sf::Keyboard::D) {
										appState = State::Generate;
										algState = AlgorithmState::IterativeDFS;
								} 
								// Key binding R resets maze
								else if(event.key.code == sf::Keyboard::R) {
										for(int i = 0; i < numCellWidth; i++) {
												for(int k = 0; k < numCellHeight; k++) {
														grid[i][k].reset();
												}
										}
										dfsAlgorithm.finished = false;
										dfsAlgorithm.setGrid(grid);
										appState = State::Idle;
										algState = AlgorithmState::None;
								} 
								// Key binding V toggles Hud visibility
								else if(event.key.code == sf::Keyboard::V) {
										HudVisibility = !HudVisibility;
										if(HudVisibility) {
												algorithmMenu.displayButtons = true;
										} else {
												algorithmMenu.displayButtons = false;
										}
								} 

						// Check for mouse press
						case sf::Event::MouseButtonPressed:
								{
								if(event.mouseButton.button == sf::Mouse::Left) {
										sf::Vector2i point = sf::Mouse::getPosition(*window);
										algorithmMenu.clicked(point);
										
										// Check whether the DFS Button was pressed
										if(generateMazeDFSButton.clicked(point) && algorithmMenu.displayButtons) {
												appState = State::Generate;
												algState = AlgorithmState::IterativeDFS;
										} 

										// Check whether the HK Button was pressed
										else if(generateMazeHKButton.clicked(point) && algorithmMenu.displayButtons) {
												appState = State::Generate;
												algState = AlgorithmState::HuntkillAlgo;
										}
										
										// Check whether the Restart Button was pressed
										else if(restartMazeButton.clicked(point)) {
												for(int i = 0; i < numCellWidth; i++) {
														for(int k = 0; k < numCellHeight; k++) {
																grid[i][k].reset();
														}
												}
												dfsAlgorithm.finished = false;
												dfsAlgorithm.setGrid(grid);
												hkAlgorithm.finished = false;
												hkAlgorithm.setGrid(grid);
												appState = State::Idle;
												algState = AlgorithmState::None;
										}
								}
								}
								break;
						default:
								break;
				}
		}
}

void Application::update() {
		// Check Application state
		switch(appState) {
				// Application is IDLE
				case State::Idle:
						break;

				// Application is in generate state
				case State::Generate:
						for(size_t i = 0; i < grid.size(); i++) {
								for(size_t k = 0; k < grid[i].size(); k++) {
										grid[i][k].reset();
								}
						}
						clock.restart();
						
						// Check which algorithm is chosen
						switch(algState) {
								// Run Iterative Depth First Search
								case AlgorithmState::IterativeDFS:
										generateMazeDFS();
										hkAlgorithm.finished = true;
										break;
								// Run Hunt Kill Algorithm
								case AlgorithmState::HuntkillAlgo:
										generateMazeHK();
										dfsAlgorithm.finished = true;
										break;
								default:
										break;
						}
						// Reset states after algorithm finished
						algState = AlgorithmState::None;
						appState = State::Idle;
						break;
				default:
						break;
		}
}

bool Application::isRunning() {
		return window->isOpen();
}

void Application::createGrid() {
		// Create basic graph
		for(int i = 0; i < numCellWidth; i++) {
				for(int k = 0; k < numCellHeight; k++) {
						Cell c(i*cellSize, k*cellSize, cellSize, i, k);
						grid[i][k] = c;
				}
		}
}

void Application::createUI() {
		// Create UI 
		sf::Vector2f size(110, 30);

		// Create Buttons
		generateMazeDFSButton = Button(width/30, height/50 + size.y , size, "Iterative DFS");
		generateMazeHKButton = Button(width/30, height/50 + 2*size.y, size, "Hunt Kill");
		restartMazeButton = Button(width - width/30 - size.x, height/50, size, "Restart Maze");
		
		// Add Buttons to Menu list
		algorithmMenu = Menu(width/30, height/50, size, "Algorithms");
		algorithmMenu.addButton(generateMazeDFSButton);
		algorithmMenu.addButton(generateMazeHKButton);
}

void Application::generateMazeDFS() {
		while(!dfsAlgorithm.finished) {
				window->pollEvent(event);
				if(clock.getElapsedTime().asMilliseconds() > 50) {
						window->clear(sf::Color(32, 32, 32));
						dfsAlgorithm.generate();
						dfsAlgorithm.render(window);
						window->display();
						clock.restart();
				}
		}
		grid = dfsAlgorithm.getUpdatedMaze();
}

void Application::generateMazeHK() {
		while(!hkAlgorithm.finished) {
				window->pollEvent(event);
				if(clock.getElapsedTime().asMilliseconds() > 50) {
						window->clear(sf::Color(32, 32, 32));
						hkAlgorithm.generate();
						hkAlgorithm.render(window);
						window->display();
						clock.restart();
				}
		}
		grid = hkAlgorithm.getUpdatedMaze();
}
