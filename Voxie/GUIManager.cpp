#include "GUIManager.h"

namespace Voxie {
	GUIManager::GUIManager() {}

	bool GUIManager::init(GLFWwindow* window) {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		return true;
	}

	// return if app should close window
	bool GUIManager::setup(GLFWwindow* window) {
		bool windowShouldClose = false;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// imgui components
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("New", "Ctrl+N")) {
					std::cout << "Open new file" << std::endl;
				}
				if (ImGui::MenuItem("Open", "Ctrl+O")) {
					std::cout << "Open file" << std::endl;
				}
				if (ImGui::MenuItem("Close", "Ctrl+W")) {
					std::cout << "Close file" << std::endl;
				}
				if (ImGui::MenuItem("Save", "Ctrl+S")) {
					std::cout << "Save file" << std::endl;
				}
				if (ImGui::MenuItem("Save as")) {
					std::cout << "Save file as" << std::endl;
				}
				if (ImGui::MenuItem("Quit", "Alt+F4")) {
					windowShouldClose = true;
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Debug")) {
				if (ImGui::MenuItem("Demo Window")) {
				}
				if (ImGui::MenuItem("Debug Info")) {
				}
				if (ImGui::MenuItem("Arrow Panel")) {
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		return windowShouldClose;
	}

	void GUIManager::cleanup() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void GUIManager::render() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
