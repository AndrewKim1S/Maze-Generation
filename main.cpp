#include "Application.h"
#include <iostream>


int main() {
		srand(static_cast<unsigned>(time(0)));

		// Width and Height of the window must be multiple of 25;
		// 1500 by 900 is default
		Application sim = Application(1500, 900);

		while(sim.isRunning()) {
				sim.run();
		}

		return 0;
}
