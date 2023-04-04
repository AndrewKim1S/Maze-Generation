#include "Application.h"


Application::Application() {

}

Application::Application(int w, int h) {
		window = new sf::RenderWindow(sf::VideoMode(w, h), "Maze Generation");
		window->setPosition(sf::Vector2i(200, 75));
		width = w;
		height = h;

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
				// generateMazeDFSButton.render(window);
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
						case sf::Event::Closed:
								window->close();
								break;
						case sf::Event::KeyPressed:
								if(event.key.code == sf::Keyboard::Escape) {
										window->close();
								}	else if(event.key.code == sf::Keyboard::D) {
										appState = State::Generate;
										algState = AlgorithmState::IterativeDFS;
								} else if(event.key.code == sf::Keyboard::R) {
										for(int i = 0; i < numCellWidth; i++) {
												for(int k = 0; k < numCellHeight; k++) {
														grid[i][k].reset();
												}
										}
										dfsAlgorithm.finished = false;
										dfsAlgorithm.setGrid(grid);
										appState = State::Idle;
										algState = AlgorithmState::None;
								} else if(event.key.code == sf::Keyboard::V) {
										HudVisibility = !HudVisibility;
								} 
						case sf::Event::MouseButtonPressed:
								{
								if(event.mouseButton.button == sf::Mouse::Left) {
										sf::Vector2i point = sf::Mouse::getPosition(*window);
										algorithmMenu.clicked(point);
										if(generateMazeDFSButton.clicked(point) && algorithmMenu.displayButtons) {
												appState = State::Generate;
												algState = AlgorithmState::IterativeDFS;
										} 
										
										else if(restartMazeButton.clicked(point)) {
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
								}
								}
								break;
						default:
								break;
				}
		}
}

void Application::update() {
		switch(appState) {
				case State::Idle:
						break;
				case State::Generate:
						for(size_t i = 0; i < grid.size(); i++) {
								for(size_t k = 0; k < grid[i].size(); k++) {
										grid[i][k].reset();
								}
						}
						clock.restart();
						
						switch(algState) {
								case AlgorithmState::IterativeDFS:
										generateMazeDFS();
										break;
								default:
										break;
						}
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
		for(int i = 0; i < numCellWidth; i++) {
				for(int k = 0; k < numCellHeight; k++) {
						Cell c(i*cellSize, k*cellSize, cellSize, i, k);
						grid[i][k] = c;
				}
		}
}

void Application::createUI() {
		sf::Vector2f size(110, 30);

		generateMazeDFSButton = Button(width/30, height/50 + size.y , size, "Iterative DFS");
		restartMazeButton = Button(width - width/30 - size.x, height/50, size, "Restart Maze");
		
		algorithmMenu = Menu(width/30, height/50, size, "Algorithms");
		algorithmMenu.addButton(generateMazeDFSButton);
}

void Application::generateMazeDFS() {
		while(!dfsAlgorithm.finished) {
				window->pollEvent(event);
				if(clock.getElapsedTime().asMilliseconds() > 50) {
						window->clear(sf::Color(44, 105, 141));
						dfsAlgorithm.generate();
						dfsAlgorithm.render(window);
						window->display();
						clock.restart();
				}
		}
		grid = dfsAlgorithm.getUpdatedMaze();
}
