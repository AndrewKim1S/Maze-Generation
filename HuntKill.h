#pragma once

#include <iostream>
#include "Cell.h"


class HuntKill {
		
		public:
				bool finished;

				HuntKill();
				HuntKill(std::vector<std::vector<Cell>>& g);
				~HuntKill();
				void generate();
				void search();
				void setGrid(std::vector<std::vector<Cell>>& g);
				void render(sf::RenderTarget* target);
				std::vector<std::vector<Cell>> getUpdatedMaze();
				void printForTesting();

		private:
				std::vector<std::vector<Cell>> grid;
				Cell* current;
				Cell* adjacent;
};
