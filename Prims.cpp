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
		
		// Check that there are still cells left to add to the maze
		if(inMaze.size() >= grid.size() * grid[0].size() && frontier.size() == 0) {
				finished = true;
				return;
		}

		// If there are no cells in the maze, select one at random
		if(inMaze.size() == 0) {
				size_t x = rand() % static_cast<int>(grid.size());
				size_t y = rand() % static_cast<int>(grid[0].size());
				inMaze.push_back(&grid[x][y]);
				grid[x][y].visited = true;
		
				// Check Adjacent cells and add them to frontier if they are not 
				// visited and within the grid
				// Top neighbor cell
				if(y-1 >= 0 && !grid[x][y-1].visited) {
						frontier.push_back(&grid[x][y-1]);
				}
				// Bottom neighbor cell
				if(y+1 < grid[x].size() && !grid[x][y+1].visited) {
						frontier.push_back(&grid[x][y+1]);
				}
				// Left neighbor cell
				if(x-1 >= 0 && !grid[x-1][y].visited) {
						frontier.push_back(&grid[x-1][y]);
				}
				// Right neighbor cell
				if(x+1 < grid.size() && !grid[x+1][y].visited) {
						frontier.push_back(&grid[x+1][y]);
				}
		}

		// Choose a random cell from Frontier vector
		// Then carve a passage to a random adjacent cell that is inMaze
		sf::Vector2f g;

		int randCell = rand() % frontier.size();
		Cell* chosenOne = frontier[randCell];
		frontier.erase(frontier.begin() + randCell);
		Cell* adjacent;
		g = chosenOne->getGridPos();
		bool cellsFound = false;

		std::cout << "I swear to fucking god" << std::endl;

		// Loop through until a suitable cell is found
		while(!cellsFound) {
				
				int randAdjacentCell = rand() % 4;

				switch(randAdjacentCell) {
						case 0:
								if(g.y-1 >= 0 && grid[g.x][g.y-1].visited) {
										adjacent = &grid[g.x][g.y-1];
										chosenOne->visited = true;
										chosenOne->removeWall(1);
										adjacent->removeWall(4);
										cellsFound = true;
										inMaze.push_back(chosenOne);
								}
								break;
						case 1:
								if(g.y+1 < grid[g.x].size() && grid[g.x][g.y+1].visited) {
										adjacent = &grid[g.x][g.y+1];
										chosenOne->visited = true;
										chosenOne->removeWall(4);
										adjacent->removeWall(1);
										cellsFound = true;
										inMaze.push_back(chosenOne);
								}
								break;
						case 2:
								if(g.x-1 >= 0 && grid[g.x-1][g.y].visited) {
										adjacent = &grid[g.x-1][g.y];
										chosenOne->visited = true;
										chosenOne->removeWall(2);
										adjacent->removeWall(3);
										cellsFound = true;
										inMaze.push_back(chosenOne);
								}
								break;
						case 3:
								if(g.x+1 < grid.size() && grid[g.x+1][g.y].visited) {
										adjacent = &grid[g.x+1][g.y];
										chosenOne->visited = true;
										chosenOne->removeWall(3);
										adjacent->removeWall(2);
										cellsFound = true;
										inMaze.push_back(chosenOne);
								}
								break;
						default:
								break;
				} 
		}

		int x = chosenOne->getGridPos().x;
		int y = chosenOne->getGridPos().y;

		// Check Adjacent cells and add them to frontier if they are not 
		// visited and within the grid
		// Top neighbor cell
		if(y-1 >= 0 && !grid[x][y-1].visited) {
				frontier.push_back(&grid[x][y-1]);
		}
		// Bottom neighbor cell
		if(y+1 < static_cast<int>(grid[x].size()) && !grid[x][y+1].visited) {
				frontier.push_back(&grid[x][y+1]);
		}
		// Left neighbor cell
		if(x-1 >= 0 && !grid[x-1][y].visited) {
				frontier.push_back(&grid[x-1][y]);
		}
		// Right neighbor cell
		if(x+1 < static_cast<int>(grid.size()) && !grid[x+1][y].visited) {
				frontier.push_back(&grid[x+1][y]);
		}

		// printForTesting();
		
}

void Prims::setGrid(std::vector<std::vector<Cell>>& g) {
		grid = g;
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
