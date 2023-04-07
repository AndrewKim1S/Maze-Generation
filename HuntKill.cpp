#include "HuntKill.h"


HuntKill::HuntKill(){
		finished = false;
}

HuntKill::HuntKill(std::vector<std::vector<Cell>>& g) {
		grid = g;
		finished = false;
}

HuntKill::~HuntKill() {

}

void HuntKill::generate() {
		if(current == NULL) {
				std::cout << "yay null ptr" << std::endl;
		}
}

void HuntKill::setGrid(std::vector<std::vector<Cell>>& g) {
		grid = g;
}

void HuntKill::render(sf::RenderTarget* target) {
		
}

std::vector<std::vector<Cell>> HuntKill::getUpdatedMaze() {
		return grid;
}
