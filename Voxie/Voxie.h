#ifndef VOXIE_H
#define VOXIE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image\stb_image.h>

#include "Global.h"
#include "GUIManager.h"
#include "Scene.h"

namespace Voxie {
	class Core {
	public:
		GLFWwindow * window;

		GUIManager guiManager;
		Scene mainScene;

		Core();

		bool init();
		void mainLoop();
		void cleanup();
	private:
	};
}

#endif