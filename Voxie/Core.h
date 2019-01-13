#ifndef CORE_H
#define CORE_H

#include "Global.h"
#include "DataManager.h"
#include "Renderer.h"
#include "MousePicker.h"

namespace Voxie {
	class Core {
	public:
		DataManager dataManager;
		Renderer renderer;
		MousePicker mousePicker;

		Core();

		bool init();
		void mainLoop();
		void cleanup();
	private:
	};
}

#endif