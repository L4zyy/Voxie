#include "GUIManager.h"
#include "Core.h"

namespace Voxie {
	GUIManager::GUIManager() {
		arrowMode = true;
		camSpeed = 10.0f;
		eyeSpeed = 10.0f;
		zoomSpeed = 10.0f;
	}

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
		static ImVec2 mainMenuBarSize;
		static ImVec2 debugInfoSize;
		static ImVec2 actionBarSize;
		static ImVec2 toolBarSize;

		static bool windowShouldClose = false;

		static bool displayDemowindow = false;
		static bool displayDebugInfo = true;
		static bool displayArrowPanel = true;
		static bool displayActionBar = true;
		static bool displayToolBar = true;

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

			if (ImGui::BeginMenu("Tools")) {
				if (ImGui::MenuItem("Demo Window", nullptr, displayDemowindow))
					displayDemowindow = !displayDemowindow;
				if (ImGui::MenuItem("Debug Info", nullptr, displayDebugInfo))
					displayDebugInfo = !displayDebugInfo;
				if (ImGui::MenuItem("Arrow Panel", nullptr, displayArrowPanel))
					displayArrowPanel = !displayArrowPanel;
				if (ImGui::MenuItem("Action Bar", nullptr, displayActionBar))
					displayActionBar = !displayActionBar;
				if (ImGui::MenuItem("Tool Bar", nullptr, displayToolBar))
					displayToolBar = !displayToolBar;
				ImGui::EndMenu();
			}

			// display FPS
			int indent = 100;
			ImGui::Indent(ImGui::GetIO().DisplaySize.x - indent);
			ImGui::Text("FPS: %.1f", core->renderer.FPS);

			mainMenuBarSize = ImGui::GetWindowSize();

			ImGui::EndMainMenuBar();
		}

		if (displayDemowindow) ImGui::ShowDemoWindow(&displayDemowindow);
		if (displayDebugInfo) showDebugInfo(&displayDebugInfo, mainMenuBarSize.y + actionBarSize.y, debugInfoSize);
		if (displayArrowPanel) showArrowPanel(&displayArrowPanel, mainMenuBarSize.y + actionBarSize.y);
		if (displayActionBar) showActionBar(&displayActionBar, ImVec2(0.0f, mainMenuBarSize.y), actionBarSize);
		if (displayToolBar) showToolBar(&displayToolBar, ImVec2(0.0f, mainMenuBarSize.y + actionBarSize.y), toolBarSize);

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


	void GUIManager::showDebugInfo(bool* open, float viewY, ImVec2& size) {
		static const float DISTANCE = 10.0f;
		static int corner = 3;
		ImVec2 windowPos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? ImGui::GetIO().DisplaySize.y - DISTANCE : viewY + DISTANCE);
		ImVec2 windowPosPivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
		ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPosPivot);
		ImGui::SetNextWindowBgAlpha(0.3f);
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 10.0f;

		if (ImGui::Begin("Debug Info", open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav)) {
			ImGui::Text("Debug Information");
			ImGui::Separator();
			ImGui::Text("--- IO ---");
			ImGui::Separator();
			ImGui::Text("Screen Scale: (%.1f, %.1f)", core->renderer.scr_width, core->renderer.scr_height);
			ImGui::Text("Mouse Position: (%.1f, %.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
			ImGui::Text("Camera Position: (%.1f, %.1f, %.1f)", core->renderer.mainScene.camera.Position.x, core->renderer.mainScene.camera.Position.y, core->renderer.mainScene.camera.Position.z);
			ImGui::Text("Camera Direction: (%.1f, %.1f, %.1f)", core->renderer.mainScene.camera.Front.x, core->renderer.mainScene.camera.Front.y, core->renderer.mainScene.camera.Front.z);
			glm::vec3 currentRay = core->mousePicker.getCurrentRay();
			ImGui::Text("Mouse Ray: (%.1f, %.1f, %.1f)", currentRay.x, currentRay.y, currentRay.z);
			ImGui::Separator();
			ImGui::Text("--- Scene ---");
			ImGui::Separator();
			ImGui::Text("Voxel Count: %d", core->renderer.mainScene.voxels.size());

			if (ImGui::BeginPopupContextWindow()) {
				if (ImGui::MenuItem("Top Left", nullptr, corner == 0)) corner = 0;
				if (ImGui::MenuItem("Top Right", nullptr, corner == 1)) corner = 1;
				if (ImGui::MenuItem("Bottom Left", nullptr, corner == 2)) corner = 2;
				if (ImGui::MenuItem("Bottom Right", nullptr, corner == 3)) corner = 3;
				if (open && ImGui::MenuItem("Close")) *open = false;

				ImGui::EndPopup();
			}

			size = ImGui::GetWindowSize();

			ImGui::End();
		}
	}
	void GUIManager::showArrowPanel(bool* open, float viewY) {
		static const float DISTANCE = 10.0f;
		static int corner = 1;
		ImVec2 windowPos = ImVec2(ImGui::GetIO().DisplaySize.x - DISTANCE, viewY + DISTANCE);
		ImVec2 windowPosPivot = ImVec2(1.0f, 0.0f);
		ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPosPivot);
		ImGui::SetNextWindowBgAlpha(0.1f);
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 10.0f;

		if (ImGui::Begin("Arrow Panel", open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav)) {
			if (ImGui::Button(arrowMode ? "Pos Mode" : "Eye Mode"))
				arrowMode = !arrowMode;

			static float arrowSize = ImGui::GetFrameHeight();

			ImGui::Separator();
			ImGui::Indent(arrowSize + 2.0f);
			ImGui::ArrowButton("ArrowFront", ImGuiDir_Up);
			if (ImGui::IsItemHovered() && ImGui::IsMouseDown(0)) {
				if (arrowMode)
					core->renderer.mainScene.camera.changePosition(UP, camSpeed * core->renderer.deltaTime);
				else
					core->renderer.mainScene.camera.changeDirection(UP, eyeSpeed * core->renderer.deltaTime);
			}
			ImGui::Unindent();
			ImGui::ArrowButton("ArrowLeft", ImGuiDir_Left);
			if (ImGui::IsItemHovered() && ImGui::IsMouseDown(0)) {
				if (arrowMode)
					core->renderer.mainScene.camera.changePosition(LEFT, camSpeed * core->renderer.deltaTime);
				else
					core->renderer.mainScene.camera.changeDirection(LEFT, eyeSpeed * core->renderer.deltaTime);
			}
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(arrowSize -12.0f, arrowSize));
			ImGui::SameLine();
			ImGui::ArrowButton("ArrowRight", ImGuiDir_Right);
			if (ImGui::IsItemHovered() && ImGui::IsMouseDown(0)) {
				if (arrowMode)
					core->renderer.mainScene.camera.changePosition(RIGHT, camSpeed * core->renderer.deltaTime);
				else
					core->renderer.mainScene.camera.changeDirection(RIGHT, eyeSpeed * core->renderer.deltaTime);
			}
			ImGui::Indent(arrowSize + 2.0f);
			ImGui::ArrowButton("ArrowBack", ImGuiDir_Down);
			if (ImGui::IsItemHovered() && ImGui::IsMouseDown(0)) {
				if (arrowMode)
					core->renderer.mainScene.camera.changePosition(DOWN, camSpeed * core->renderer.deltaTime);
				else
					core->renderer.mainScene.camera.changeDirection(DOWN, eyeSpeed * core->renderer.deltaTime);
			}
			ImGui::Unindent();
			ImGui::Indent(7.5f);
			ImGui::ArrowButton("ArrowUp", ImGuiDir_Up);
			if (ImGui::IsItemHovered() && ImGui::IsMouseDown(0)) {
				if (arrowMode)
					core->renderer.mainScene.camera.changePosition(FORWARD, camSpeed * core->renderer.deltaTime);
				else
					core->renderer.mainScene.camera.changeZoom(FORWARD, zoomSpeed * core->renderer.deltaTime);
			}
			ImGui::SameLine();
			ImGui::ArrowButton("ArrowDown", ImGuiDir_Down);
			if (ImGui::IsItemHovered() && ImGui::IsMouseDown(0)) {
				if (arrowMode)
					core->renderer.mainScene.camera.changePosition(BACKWARD, camSpeed * core->renderer.deltaTime);
				else
					core->renderer.mainScene.camera.changeZoom(BACKWARD, zoomSpeed * core->renderer.deltaTime);
			}
			ImGui::Unindent();

			if (ImGui::BeginPopupContextWindow()) {
				if (ImGui::MenuItem("Top Left", nullptr, corner == 0)) corner = 0;
				if (ImGui::MenuItem("Top Right", nullptr, corner == 1)) corner = 1;
				if (ImGui::MenuItem("Bottom Left", nullptr, corner == 2)) corner = 2;
				if (ImGui::MenuItem("Bottom Right", nullptr, corner == 3)) corner = 3;
				if (open && ImGui::MenuItem("Close")) *open = false;

				ImGui::EndPopup();
			}

			ImGui::End();
		}
	}
	void GUIManager::showActionBar(bool* open, ImVec2 windowPos, ImVec2& size) {
		static const float DISTANCE = 10.0f;
		ImGui::SetNextWindowPos(windowPos, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 40.0f));
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
		style.WindowRounding = 0.0f;

		if (ImGui::Begin("Action Bar", open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav)) {
			if (ImGui::Button("<")) {}
			ImGui::SameLine();
			if (ImGui::Button(">")) {}
			ImGui::SameLine();
			if (ImGui::Button(core->renderer.mainScene.editMode ? "Edit Mode" : "View Mode")) {
				core->renderer.mainScene.editMode = !core->renderer.mainScene.editMode;
			}

			size = ImGui::GetWindowSize();

			ImGui::End();
		}

		ImGui::StyleColorsDark();
	}
	void GUIManager::showToolBar(bool* open, ImVec2 windowPos, ImVec2& size) {
		static const float MIN_WIDTH = 250.0f;
		ImGui::SetNextWindowPos(windowPos, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSizeConstraints(ImVec2(MIN_WIDTH, ImGui::GetIO().DisplaySize.y - windowPos.y), ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y - windowPos.y));
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 0.0f;

		if (ImGui::Begin("Tool Bar", open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav)) {
			// color editor
			{
				ImVec4 editorColor = ImColor(core->dataManager.currentColor.x, core->dataManager.currentColor.y, core->dataManager.currentColor.z);
				ImGui::ColorEdit3("Current Color", (float*)&editorColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_Float);

				static bool initPalette = false;
				static const int paletteColorNumber = 32;
				static ImVec4 paletteColors[paletteColorNumber];
				if (!initPalette) {
					for (size_t i = 0; i < paletteColorNumber; i++) {
						ImGui::ColorConvertHSVtoRGB(i / 31.0f, 0.8f, 0.8f, paletteColors[i].x, paletteColors[i].y, paletteColors[i].z);
						paletteColors[i].w = 1.0f;
					}

					if (!initPalette)
						initPalette = true;
				}

				for (size_t i = 0; i < paletteColorNumber; i++) {
					ImGui::PushID(i);

					if ((i % (paletteColorNumber / 4)) != 0)
						ImGui::SameLine();
					if (ImGui::ColorButton("##palette", paletteColors[i], ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip, ImVec2(20, 20)))
						core->dataManager.currentColor = glm::vec3(paletteColors[i].x, paletteColors[i].y, paletteColors[i].z);

					ImGui::PopID();
				}
			}

			ImGui::NewLine();
			ImGui::Separator();
			ImGui::Spacing();

			// properties
			if (core->dataManager.currentVoxel) {
				Voxel* currentVoxel = core->dataManager.currentVoxel;
				if (ImGui::CollapsingHeader("Properties")) {
					ImGui::Spacing();
					ImGui::Text("Color: ");
					ImGui::SameLine();
					ImVec4 voxelColor = ImVec4(currentVoxel->Color.x, currentVoxel->Color.y, currentVoxel->Color.z, 1.0f);
					if (ImGui::ColorEdit3("Properties##Color", (float*)&voxelColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_Float)) {
						currentVoxel->Color = glm::vec3(voxelColor.x, voxelColor.y, voxelColor.z);
						core->renderer.mainScene.updateVoxels();
					}

					ImGui::Text("Position: ");
					ImGui::SameLine();
					ImGui::Text(getVec3String(currentVoxel->Position).c_str());
				}
			}

			size = ImGui::GetWindowSize();

			ImGui::End();

		}
	}
}
