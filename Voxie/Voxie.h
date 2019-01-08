#ifndef VOXIE_H
#define VOXIE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image\stb_image.h>

#include "Global.h"
#include "GUIManager.h"
#include "Scene.h"

class Voxie {
public:
	GLFWwindow* window;

	GUIManager guiManager;
	Scene mainScene;

	Voxie();

	bool init();
	void mainLoop();
	void cleanup();
private:
};

#endif