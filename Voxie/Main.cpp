#include <iostream>

#include "Global.h"
#include "Voxie.h"

using namespace std;

int main() {
	Voxie app;

	app.init();

	app.mainLoop();

	app.cleanup();

	return 0;
}
