#include "DepthFirst.h"


DepthFirst::DepthFirst() {
		finished = false;
}

DepthFirst::DepthFirst(std::vector<std::vector<Cell>>& g) {
		grid = g;
		finished = false;
		queue = std::stack<Cell*>();
}

DepthFirst::~DepthFirst() {

}

void DepthFirst::generate() {
		Cell* current;
		Cell* adjacent;

		if(queue.size() > 0) {
				current = queue.top();
		} else {
				int x = rand() % static_cast<int>(grid.size());
				int y = rand() % static_cast<int>(grid[0].size());
				current = &grid[x][y];
				current->visited = true;
				queue.push(current);
		}

		sf::Vector2f g = current->getGridPos();
		current->setColor();

		bool cellsFound = false;
		
		while(!cellsFound) {

				bool top = false;
				bool bot = false;
				bool left = false;
				bool right = false;
				if(g.y-1 >= 0 && grid[g.x][g.y-1].visited == false) {
						top = true;
				}
				if(g.y+1 < grid[g.x].size() && grid[g.x][g.y+1].visited == false) {
						bot = true;
				}
				if(g.x-1 >= 0 && grid[g.x-1][g.y].visited == false) {
						left = true;
				}
				if(g.x+1 < grid.size() && grid[g.x+1][g.y].visited == false) {
						right = true;
				}
				if(!top && !bot && !left && !right) {
						if(queue.size() == 0) {
								finished = true;
								return;
						} else {
								current = queue.top();
								queue.pop();
								g = current->getGridPos();
						}
				}

				int randAdjacentCell = rand() % 4;
				
				switch(randAdjacentCell) {
						case 0:
								if(top) {
										adjacent = &grid[g.x][g.y-1];
										adjacent->visited = true;
										cellsFound = true;
										queue.push(adjacent);
										current->removeWall(1);
										adjacent->removeWall(4);
								}
								break;
						case 1:
								if(left) {
										adjacent = &grid[g.x-1][g.y];
										adjacent->visited = true;
										cellsFound = true;
										queue.push(adjacent);
										current->removeWall(2);
										adjacent->removeWall(3);
								}
								break;
						case 2:
								if(right) {
										adjacent = &grid[g.x+1][g.y];
										adjacent->visited = true;
										cellsFound = true;
										queue.push(adjacent);
										current->removeWall(3);
										adjacent->removeWall(2);
								}
								break;
						case 3:
								if(bot) {
										adjacent = &grid[g.x][g.y+1];
										adjacent->visited = true;
										cellsFound = true;
										queue.push(adjacent);
										current->removeWall(4);
										adjacent->removeWall(1);
								}
								break;
						default:
								break;
				}

				adjacent->setSelectedColor();
		}

		/*std::cout << "current: " << current->getGridPos().x << ", " << current->getGridPos().y
				<< " visit: " << current->visited << std::endl;
		std::cout << "adjacent: " << adjacent->getGridPos().x << ", " << adjacent->getGridPos().y
				<< " visit: " << adjacent->visited << std::endl;
		printForTesting();*/

}

void DepthFirst::setGrid(std::vector<std::vector<Cell>>& g) {
		grid = g;
}

void DepthFirst::printForTesting() {
		for(size_t i = 0; i < grid.size(); i++) {
				for(size_t k = 0; k < grid[i].size(); k++) {
						std::cout << i << ", " << k << ": top: " << grid[i][k].top <<
								" left: " << grid[i][k].left << 
								" right: " << grid[i][k].right << 
								" bottom: " << grid[i][k].bottom <<
								" visited: " << grid[i][k].visited << std::endl;
				}
		}
}

void DepthFirst::render(sf::RenderTarget* window) {
		for(size_t i = 0; i < grid.size(); i++) {
				for(size_t k = 0; k < grid[i].size(); k++) {
						grid[i][k].render(window);
				}
		}
}

std::vector<std::vector<Cell>> DepthFirst::getUpdatedMaze() {
		return grid;
}
