#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "Global.h"
#include "Scene.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace Voxie {
	class GUIManager {
	public:
		Scene* mainScene;

		bool arrowMode;

		GUIManager();
		bool init(GLFWwindow* window);
		bool setup(GLFWwindow* window, float FPS);
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