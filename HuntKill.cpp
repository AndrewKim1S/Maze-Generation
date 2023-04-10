#include "HuntKill.h"


HuntKill::HuntKill(){
		finished = false;
}

HuntKill::HuntKill(std::vector<std::vector<Cell>>& g) {
		grid = g;
		finished = false;
		current = NULL;
		adjacent = NULL;
}

HuntKill::~HuntKill() {

}

void HuntKill::generate() {
		if(current == NULL) {
				int x = rand() % static_cast<int>(grid.size());
				int y = rand() % static_cast<int>(grid[0].size());
				current = &grid[x][y];
				current->visited = true;
		}
		
		sf::Vector2f g = current->getGridPos();
		current->setColor();

		bool cellsFound = false;

		while(!cellsFound) {
				
				bool top = false;
				bool bot = false;
				bool left = false;
				bool right = false;

				if(g.y-1 >= 0 && !grid[g.x][g.y-1].visited) {
						top = true;
				}
				if(g.y+1 < grid[g.x].size() && !grid[g.x][g.y+1].visited) {
						bot = true;
				}
				if(g.x-1 >= 0 && grid[g.x-1][g.y].visited == false) {
						left = true;
				}
				if(g.x+1 < grid.size() && grid[g.x+1][g.y].visited == false) {
						right = true;
				}

				// Hunt Kill
				if(!top && !bot && !left && !right) {
						bool found = false;
						for(size_t i = 0; i < grid[0].size(); i++) {

								for(size_t k = 0; k < grid.size(); k++) {
										
										if(!grid[k][i].visited) {
												bool t = false;
												bool l = false;
												bool r = false;
												bool b = false;
												g = grid[k][i].getGridPos();

												// Check that there is a neighbor that has been visited 
												if(g.y-1 >= 0 && grid[g.x][g.y-1].visited) {
														t = true;
												}
												if(g.y+1 < grid[g.x].size() && grid[g.x][g.y+1].visited) {
														b = true;
												}
												if(g.x-1 >= 0 && grid[g.x-1][g.y].visited) {
														l = true;
												}
												if(g.x+1 < grid.size() && grid[g.x+1][g.y].visited) {
														r = true;
												}

												if(!t && !b && !l && !r) {
														continue;
												}

												bool valid = false;
												while (!valid) {

												int randAdjacentCell = rand() % 4;
												current = &grid[k][i];
												current->setColor();
												
												switch(randAdjacentCell) {
														case 0:
																if(t) {
																		adjacent = &grid[g.x][g.y-1];
																		current->removeWall(1);
																		adjacent->removeWall(4);
																		current->visited = true;
																		valid = true;
																}
																break;
														case 1:
																if(l) {
																		adjacent = &grid[g.x-1][g.y];
																		current->removeWall(2);
																		adjacent->removeWall(3);
																		current->visited = true;
																		valid = true;
																}
																break;
														case 2:
																if(r) {
																		adjacent = &grid[g.x+1][g.y];
																		current->removeWall(3);
																		adjacent->removeWall(2);
																		current->visited = true;
																		valid = true;
																}
																break;
														case 3:
																if(b) {
																		adjacent = &grid[g.x][g.y+1];
																		current->removeWall(4);
																		adjacent->removeWall(1);
																		current->visited = true;
																		valid = true;
																}
																break;
														default:
																break;
												}
												}

												found = true;
												break;
										}
								}

								if(found) {
										break;
								}
						}

						if(!found) {
								finished = true;
								return;
						}
				}

				int randAdjacentCell = rand() % 4;

				switch(randAdjacentCell) {
						case 0:
								if(top) {
										adjacent = &grid[g.x][g.y-1];
										adjacent->visited = true;
										cellsFound = true;
										current->removeWall(1);
										adjacent->removeWall(4);
								}
								break;
						case 1:
								if(left) {
										adjacent = &grid[g.x-1][g.y];
										adjacent->visited = true;
										cellsFound = true;
										current->removeWall(2);
										adjacent->removeWall(3);
								}
								break;
						case 2:
								if(right) {
										adjacent = &grid[g.x+1][g.y];
										adjacent->visited = true;
										cellsFound = true;
										current->removeWall(3);
										adjacent->removeWall(2);
								}
								break;
						case 3:
								if(bot) {
										adjacent = &grid[g.x][g.y+1];
										adjacent->visited = true;
										cellsFound = true;
										current->removeWall(4);
										adjacent->removeWall(1);
								}
								break;
						default:
								break;
				}
		}
		adjacent->setSelectedColor();
		current = adjacent;
}

// Implement this function into the HuntKill Generate function for readability
/* void HuntKill::search() {
		bool found = false;
		for(size_t i = 0; i < grid[0].size(); i++) {
				for(size_t k = 0; k < grid.size(); k++) {
						if(!grid[k][i].visited) {
								bool t = false;
								bool l = false;
								bool r = false;
								bool b = false;
								sf::Vector2f g = grid[k][i].getGridPos();

								// Check that there is a neighbor that has been visited 
								if(g.y-1 >= 0 && grid[g.x][g.y-1].visited) {
										t = true;
								}
								if(g.y+1 < grid[g.x].size() && grid[g.x][g.y+1].visited) {
										b = true;
								}
								if(g.x-1 >= 0 && grid[g.x-1][g.y].visited) {
										l = true;
								}
								if(g.x+1 < grid.size() && grid[g.x+1][g.y].visited) {
										r = true;
								}

								if(!t && !b && !l && !r) {
										continue;
								}

								bool valid = false;
								while (!valid) {

								int randAdjacentCell = rand() % 4;
								current = &grid[k][i];
								current->setColor();
								
								switch(randAdjacentCell) {
										case 0:
												if(t) {
														adjacent = &grid[g.x][g.y-1];
														current->removeWall(1);
														adjacent->removeWall(4);
														current->visited = true;
														valid = true;
												}
												break;
										case 1:
												if(l) {
														adjacent = &grid[g.x-1][g.y];
														current->removeWall(2);
														adjacent->removeWall(3);
														current->visited = true;
														valid = true;
												}
												break;
										case 2:
												if(r) {
														adjacent = &grid[g.x+1][g.y];
														current->removeWall(3);
														adjacent->removeWall(2);
														current->visited = true;
														valid = true;
												}
												break;
										case 3:
												if(b) {
														adjacent = &grid[g.x][g.y+1];
														current->removeWall(4);
														adjacent->removeWall(1);
														current->visited = true;
														valid = true;
												}
												break;
										default:
												break;
								}
								}

								found = true;
								return;
						}
				}

				if(found) {
						return;
				}
		}

		if(!found) {
				finished = true;
				return;
		}

} */

void HuntKill::setGrid(std::vector<std::vector<Cell>>& g) {
		grid = g;
}

void HuntKill::render(sf::RenderTarget* target) {
		for(size_t i = 0; i < grid.size(); i++) {
				for(size_t k = 0; k < grid[i].size(); k++) {
						grid[i][k].render(target);
				}
		}
}

std::vector<std::vector<Cell>> HuntKill::getUpdatedMaze() {
		return grid;
}

void HuntKill::printForTesting() {
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
