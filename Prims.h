#pragma once

#include <iostream>
#include "Cell.h"


class Prims {

		public:
				bool finished;

				Prims();
				Prims(std::vector<std::vector<Cell>>& g);
				~Prims();
				void generate();
				bool withinFrontier(Cell* c);
				void setGrid(std::vector<std::vector<Cell>> & g);
				void render(sf::RenderTarget* target);
				std::vector<std::vector<Cell>> getUpdatedMaze();
				void printForTesting();

		private:
				std::vector<std::vector<Cell>> grid;
				std::vector<Cell*> frontier;
				std::vector<Cell*> inMaze;
};
