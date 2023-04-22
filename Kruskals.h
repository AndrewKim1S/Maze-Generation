#pragma once

#include <iostream>
#include "Cell.h"


class Kruskals {

		public:
				bool finished;

				Kruskals();
				Kruskals(std::vector<std::vector<Cell>>& g);
				~Kruskals();
				void generate();
				void setGrid(std::vector<std::vector<Cell>>& g);
				void printForTesting();
				void render(sf::RenderTarget* target);
				std::vector<std::vector<Cell>> getUpdatedMaze();

		private:
				std::vector<std::vector<Cell>> grid;
};
