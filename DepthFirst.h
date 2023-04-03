#include <iostream>
#include <stack>
#include "Cell.h"


class DepthFirst {

		public:
				bool finished;

				DepthFirst();
				DepthFirst(std::vector<std::vector<Cell>>& g);
				~DepthFirst();
				void generate();
				void setGrid(std::vector<std::vector<Cell>>& g);
				void printForTesting();
				void render(sf::RenderTarget* target);
				std::vector<std::vector<Cell>> getUpdatedMaze();

		private:
				std::stack<Cell*> queue;
				std::vector<std::vector<Cell>> grid;
};
