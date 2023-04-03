#include "Application.h"


Application::Application() {

}

Application::Application(int w, int h) {
		window = new sf::RenderWindow(sf::VideoMode(w, h), "Maze Generation");
		window->setPosition(sf::Vector2i(200, 75));
		width = w;
		height = h;
		appState = State::Generate;

		numCellWidth = width/cellSize;
		numCellHeight = height/cellSize;

		grid.resize(static_cast<size_t>(numCellWidth));
		for(size_t i = 0; i < grid.size(); i++) {
				grid[i].resize(static_cast<size_t>(numCellHeight));
		}
		createGrid();

		dfsAlgorithm = DepthFirst(grid);
}

Application::~Application() {
		delete window;
}

void Application::render() {
		window->clear(sf::Color(32, 32, 32));
		for(size_t i = 0; i < grid.size(); i++) {
				for(size_t k = 0; k < grid[i].size(); k++) {
						grid[i][k].render(window);
				}
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
								}
								if(event.key.code == sf::Keyboard::G) {
										appState = State::Generate;
								}
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
						generateMaze();
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

void Application::generateMaze() {
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
