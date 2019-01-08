#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "Global.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class GUIManager {
public:
	GUIManager();
	bool init(GLFWwindow* window);
	bool setup(GLFWwindow* window);
	void cleanup();
	void render();
};

#endif