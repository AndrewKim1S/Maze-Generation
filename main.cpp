#include "Application.h"
#include <iostream>


int main() {
		srand(static_cast<unsigned>(time(0)));

		// Width and Height of the window must be multiple of 25;
		Application sim = Application(1550, 950);

		while(sim.isRunning()) {
				sim.run();
		}

		return 0;
}
