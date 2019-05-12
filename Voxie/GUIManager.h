#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Global.h"

namespace Voxie {
	class Core;

	class GUIManager {
	public:
		Core* core;

		bool arrowMode;

		float camSpeed;
		float eyeSpeed;
		float zoomSpeed;

		bool windowShouldClose;

		bool displayDemowindow;
		bool displayDebugInfo;
		bool displayArrowPanel;
		bool displayActionBar;
		bool displayToolBar;

		ImVec2 mainMenuBarSize;
		ImVec2 debugInfoSize;
		ImVec2 actionBarSize;
		ImVec2 toolBarSize;


		GUIManager();
		bool init(GLFWwindow* window);
		bool setup(GLFWwindow* window);
		void cleanup();
		void render();
	private:
		void showMainMenu();
		void showDebugInfo(bool* open, float viewY, ImVec2& size);
		void showArrowPanel(bool* open, float viewY);
		void showActionBar(bool* open, ImVec2 windowPos, ImVec2& size);
		void showToolBar(bool* open, ImVec2 windowPos, ImVec2& size);
	};
}

#endif