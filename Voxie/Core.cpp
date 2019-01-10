#include "Core.h"

namespace Voxie {
	Core::Core() {}

	bool Core::init() {
		if (!renderer.init()) {
			std::cout << "Failed to initialize renderer" << std::endl;
			return false;
		}

		return true;
	}

	void Core::mainLoop() {
		static bool appShouldClose = false;

		while (!appShouldClose) {
			appShouldClose = renderer.render();
		}
	}

	void Core::cleanup() {
		renderer.cleanup();
	}
}
