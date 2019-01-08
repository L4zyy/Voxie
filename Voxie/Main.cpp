#include <iostream>

#include "Global.h"
#include "Voxie.h"

using namespace std;

int main() {
	Voxie::Core app;

	if (!app.init()) {
		cout << "Failed to initialize Voxie" << endl;
		return -1;
	}

	app.mainLoop();

	app.cleanup();

	return 0;
}
