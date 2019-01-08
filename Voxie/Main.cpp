#include <iostream>

#include "Global.h"
#include "Core.h"

int main() {
	Voxie::Core app;

	if (!app.init()) {
		std::cout << "Failed to initialize Voxie" << std::endl;
		return -1;
	}

	app.mainLoop();

	app.cleanup();

	return 0;
}
