#include "Prims.h"


Prims::Prims() {
		finished = false;
}

Prims::Prims(std::vector<std::vector<Cell>>& g) {
		grid = g;
		finished = false;
		frontier = std::vector<Cell*>();
		inMaze = std::vector<Cell*>();
}

Prims::~Prims() {

}

void Prims::generate() {

		// If the generate algorithm has just started, choose a random cell to start with
		if(frontier.size() == 0 && inMaze.size() == 0) {

				// Choose a random starting cell
				int x = rand() % static_cast<int>(grid.size());
				int y = rand() % static_cast<int>(grid[0].size());
				Cell* chosenOne;
				chosenOne = &grid[x][y];
				chosenOne->visited = true;
				inMaze.push_back(chosenOne);
				
				// Add all adjacent cells that are in the grid into frontier
				if(x-1 >= 0) {
						frontier.push_back(&grid[x-1][y]);
				} if(x+1 < static_cast<int>(grid.size())) {
						frontier.push_back(&grid[x+1][y]);
				} if(y-1 >= 0) {
						frontier.push_back(&grid[x][y-1]);
				} if(y+1 < static_cast<int>(grid[x].size())) {
						frontier.push_back(&grid[x][y+1]);
				}
				
				for(size_t i = 0; i < frontier.size(); i++) {
						frontier[i]->setFrontierColor();
				}
				chosenOne->setColor();
		} 

		// If there are no more frontier cells and the number of cells in the maze is
		// more than 0, we can conclude that the algorithm has finished
		else if(frontier.size() == 0 && inMaze.size() > 0) {
				finished = true;
				for(size_t i = 0; i < grid.size(); i++) {
						for(size_t k = 0; k < grid[i].size(); k++) {
								grid[i][k].setColor();
						}
				}
				return;
		}

		// If there are frontier cells and cells in the maze
		else {
				// Find a random frontier cell to be added into the maze
				Cell* randFrontierCell;
				int randIndex = rand() % static_cast<int>(frontier.size());
				randFrontierCell = frontier[randIndex];
				randFrontierCell->visited = true;
				// std::cout << "randFrontierCell: " << randFrontierCell->getGridPos().x << ", " << 
						// randFrontierCell->getGridPos().y << std::endl;
				frontier.erase(frontier.begin() + randIndex);

				int x = randFrontierCell->getGridPos().x;
				int y = randFrontierCell->getGridPos().y;

				bool top = false;
				bool bot = false;
				bool left = false;
				bool right = false;

				// Find the possible adjacent cells that are in the maze
				if(x-1 >= 0 && grid[x-1][y].visited) {
						left = true;
				} if(x+1 < static_cast<int>(grid.size()) && grid[x+1][y].visited) {
						right = true;
				} if(y-1 >= 0 && grid[x][y-1].visited) {
						top = true;
				} if(y+1 < static_cast<int>(grid[x].size()) && grid[x][y+1].visited) {
						bot = true;
				}
				
				// Add cells into frontier;
				if(x-1 >= 0 && !grid[x-1][y].visited && !withinFrontier(&grid[x-1][y])) {
						frontier.push_back(&grid[x-1][y]);
				} if(x+1 < static_cast<int>(grid.size()) && !grid[x+1][y].visited && 
						!withinFrontier(&grid[x+1][y])) {
						frontier.push_back(&grid[x+1][y]);
				} if(y-1 >= 0 && !grid[x][y-1].visited && !withinFrontier(&grid[x][y-1])) {
						frontier.push_back(&grid[x][y-1]);
				} if(y+1 < static_cast<int>(grid[x].size()) && !grid[x][y+1].visited && 
						!withinFrontier(&grid[x][y+1])) {
						frontier.push_back(&grid[x][y+1]);
				}
				
				// Randomnly choose neighbor to attach with 
				bool cellFound = false;
				int neighbor;
				while(!cellFound) {
						neighbor = rand() % 4;
						if(neighbor == 0 && top) { cellFound = true; }
						else if(neighbor == 1 && left) { cellFound = true; }
						else if(neighbor == 2 && right) { cellFound = true; }
						else if(neighbor == 3 && bot) { cellFound = true; }
				}

				Cell* adjacentInMaze;

				// Break the barrier between current Frontier cell and a cell in the maze
				switch(neighbor) {
						case 0:
								adjacentInMaze = &grid[x][y-1];
								randFrontierCell->removeWall(1);
								adjacentInMaze->removeWall(4);
								break;
						case 1:
								adjacentInMaze = &grid[x-1][y];
								randFrontierCell->removeWall(2);
								adjacentInMaze->removeWall(3);
								break;
						case 2:
								adjacentInMaze = &grid[x+1][y];
								randFrontierCell->removeWall(3);
								adjacentInMaze->removeWall(2);
								break;
						case 3:
								adjacentInMaze = &grid[x][y+1];
								randFrontierCell->removeWall(4);
								adjacentInMaze->removeWall(1);
								break;
						default:
								break;
				}
				
				// std::cout << "adjacentInMaze: " << adjacentInMaze->getGridPos().x << ", " << 
						// adjacentInMaze->getGridPos().y << std::endl;

				// Coloring
				for(size_t i = 0; i < inMaze.size(); i++) {
						inMaze[i]->setColor();
				}
				for(size_t i = 0; i < frontier.size(); i++) {
						frontier[i]->setFrontierColor();
				}
				randFrontierCell->setSelectedColor();
				randFrontierCell->visited = true;
				inMaze.push_back(randFrontierCell);

				
		}
		
		// For testing purposes
		/*std::cout << "------------Printing out Frontier Vector Contents------------" << std::endl;
		for(size_t i = 0; i< frontier.size(); i++) {
				std::cout << "Index: " << i << ", Grid: " << frontier[i]->getGridPos().x << ", " << frontier[i]->getGridPos().y <<
						", visited status: " << frontier[i]->visited << std::endl; 
		}
		std::cout << "\n\n" << std::endl;*/
}

bool Prims::withinFrontier(Cell* c) {
		sf::Vector2f pos = c->getGridPos();
		for(size_t i = 0; i < frontier.size(); i++) {
				sf::Vector2f checkPos = frontier[i]->getGridPos();
				if(pos.x == checkPos.x && pos.y == checkPos.y) {
						return true;
				}
		}
		return false;
}


void Prims::setGrid(std::vector<std::vector<Cell>>& g) {
		grid = g;
		inMaze = std::vector<Cell*>();
}

void Prims::render(sf::RenderTarget* target) {
		for(size_t i = 0; i < grid.size(); i++) {
				for(size_t k = 0; k < grid[i].size(); k++) {
						grid[i][k].render(target);
				}
		}
}


std::vector<std::vector<Cell>> Prims::getUpdatedMaze() {
		return grid;
}

void Prims::printForTesting() {
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
