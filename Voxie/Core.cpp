#include "Core.h"

namespace Voxie {
	Core::Core() {
		renderer.core = this;
	}

	bool Core::init() {
		if (!renderer.init()) {
			std::cout << "Failed to initialize renderer" << std::endl;
			return false;
		}

		if (!dataManager.init(renderer.mainScene)) {
			std::cout << "Failed to initialize data manager" << std::endl;
			return false;
		}

		if (!mousePicker.init(renderer.window)) {
			std::cout << "Failed to initialize mousepicker" << std::endl;
			return false;
		}

		return true;
	}

	void Core::mainLoop() {
		static bool appShouldClose = false;

		while (!appShouldClose) {
			renderer.setup();
			mousePicker.update(renderer.mainScene.vpMatrix.view, renderer.mainScene.vpMatrix.projection);
			appShouldClose = renderer.render(mousePicker.getCurrentRay());
		}
	}

	void Core::cleanup() {
		renderer.cleanup();
	}
}
