#include "Kruskals.h"


Kruskals::Kruskals() {
		finished = false;
}

Kruskals::Kruskals(std::vector<std::vector<Cell>>& g) {
		grid = g;
		finished = false;
}

Kruskals::~Kruskals() {

}

void Kruskals::generate() {
		
}

void Kruskals::setGrid(std::vector<std::vector<Cell>>& g) {
		grid = g;
}

void Kruskals::printForTesting() {

}

void Kruskals::render(sf::RenderTarget* window) {
		
}

std::vector<std::vector<Cell>> Kruskals::getUpdatedMaze() {
		return grid;
}
