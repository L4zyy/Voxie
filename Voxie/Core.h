#ifndef CORE_H
#define CORE_H

#include "Global.h"
#include "Renderer.h"

namespace Voxie {
	class Core {
	public:
		Renderer renderer;

		Core();

		bool init();
		void mainLoop();
		void cleanup();
	private:
	};
}

#endif