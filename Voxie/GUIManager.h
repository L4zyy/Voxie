#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Global.h"

namespace Voxie {
	class Renderer;

	class GUIManager {
	public:
		Renderer* renderer;

		bool arrowMode;
		float camSpeed;
		float eyeSpeed;
		float zoomSpeed;

		GUIManager();
		bool init(GLFWwindow* window);
		bool setup(GLFWwindow* window);
		void cleanup();
		void render();
	private:
		void showDebugInfo(bool* open, float viewY, ImVec2& size);
		void showArrowPanel(bool* open, float viewY);
		void showActionBar(bool* open, ImVec2 windowPos, ImVec2& size);
		void showToolBar(bool* open, ImVec2 windowPos, ImVec2& size);
	};
}

#endif