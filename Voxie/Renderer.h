#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image\stb_image.h>

#include "Global.h"
#include "GUIManager.h"
#include "Scene.h"

namespace Voxie {
	class Core;

	class Renderer {
	public:
		Core* core;

		GLFWwindow * window;

		GUIManager guiManager;
		Scene mainScene;

		int scr_width;
		int scr_height;

		float deltaTime;
		float lastFrameTime;

		float FPS;

		float midButtonSpeed;

		Renderer();

		bool init();
		void setup();
		bool render(glm::vec3 currentMouseRay);
		void cleanup();
	private:
		void updateFPS();
		void processSceneDragging();
	};
}

#endif