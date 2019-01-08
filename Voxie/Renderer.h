#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image\stb_image.h>

#include "Global.h"
#include "GUIManager.h"
#include "Scene.h"

namespace Voxie {
	class Renderer {
	public:
		GLFWwindow * window;

		GUIManager guiManager;
		Scene mainScene;

		Renderer();

		bool init();
		bool render();
		void cleanup();
	};
}

#endif