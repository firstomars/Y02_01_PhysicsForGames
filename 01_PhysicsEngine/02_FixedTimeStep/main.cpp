#include "Application2D.h"

int main() {
	
	// allocation
	auto app = new Application2D();

	// initialise and loop
	app->run("01_FixedTimeStep", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}