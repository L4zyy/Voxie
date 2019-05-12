#include "Renderer.h"
#include "Core.h"

namespace Voxie {
	void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		Renderer* renderer = reinterpret_cast<Renderer*>(glfwGetWindowUserPointer(window));
		renderer->scr_width = width;
		renderer->scr_height = height;
	}
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
		Renderer* renderer = reinterpret_cast<Renderer*>(glfwGetWindowUserPointer(window));
		renderer->mainScene.camera.changeZoom(yoffset >= 0 ? FORWARD : BACKWARD, (float)abs(yoffset));
	}
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		static bool cancelling = false;

		// right click to cancel operation
		if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS)
			cancelling = true;

		if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
			cancelling = false;

		if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE) {
			if (!cancelling) {
				Renderer* renderer = reinterpret_cast<Renderer*>(glfwGetWindowUserPointer(window));

				// check intersection
				int index = -1;
				Direction direction = NONE;
				float distance = MAX_DISTANCE;
				Scene* pScene = &(renderer->mainScene);
				glm::vec3 mouseRay = renderer->core->mousePicker.getCurrentRay();
				glm::vec3 inverseRay = glm::vec3(1 / mouseRay.x, 1 / mouseRay.y, 1 / mouseRay.z);

				for (size_t i = 0; i < pScene->voxels.size(); i++) {
					float tmpDist;
					if (pScene->voxels[i].boundingBox.intersect(pScene->camera, inverseRay, tmpDist)) {
						if (tmpDist < distance) {
							index = i;
							distance = tmpDist;
							direction = pScene->voxels[i].boundingBox.detectIntersectionFace(pScene->camera, mouseRay, distance);
						}
					}
				}

				if (index != -1) {
					// mouse ray hit object
					if (!pScene->editMode) {
						// view mode pick voxel
						renderer->core->dataManager.currentVoxel = &renderer->mainScene.voxels[index];
					}
					else {
						// edit mode edit voxel
						if (mods == GLFW_MOD_CONTROL) {
							renderer->core->dataManager.deleteVoxel(*pScene, index);
						}
						else {
							if (direction == NONE) {
								std::cout << "Detected direction error!" << std::endl;
							}
							else {
								glm::vec3 newPosition = pScene->voxels[index].Position + getDirectionVector(direction);
								renderer->core->dataManager.addVoxel(*pScene, newPosition);
							}
						}
					}
				}
			}

			cancelling = false;
		}
	}

	Renderer::Renderer() {
		scr_width = SCR_WIDTH;
		scr_height = SCR_HEIGHT;

		midButtonSpeed = 2.5f;
	}

	bool Renderer::init() {
		// init glfw
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// create window
		window = glfwCreateWindow(scr_width, scr_height, "Voxie", nullptr, nullptr);
		if (window == nullptr) {
			std::cout << "Failed to create main window" << std::endl;
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);

		// init glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		// init GUI
		guiManager.core = core;
		if (!guiManager.init(window)) {
			std::cout << "Failed to initialize GUI" << std::endl;
			return false;
		}

		// init scene
		mainScene.init();

		// configure global opengl state
		glEnable(GL_DEPTH_TEST);

		// install callbacks
		{
			glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
			glfwSetKeyCallback(window, keyCallback);
			glfwSetScrollCallback(window, scrollCallback);
			glfwSetMouseButtonCallback(window, mouseButtonCallback);
		}

		return true;
	}

	void Renderer::setup() {
		// calculate delta time
		float currentFrameTime = (float)glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;
		updateFPS();

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// setup components
		if (guiManager.setup(window))
			glfwSetWindowShouldClose(window, true);
		mainScene.setup(scr_width, scr_height);

		processSceneDragging();
	}

	bool Renderer::render(glm::vec3 currentMouseRay) {
		mainScene.render();
		guiManager.render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		return glfwWindowShouldClose(window);
	}

	void Renderer::cleanup() {
		guiManager.cleanup();

		glfwTerminate();
	}

	void Renderer::updateFPS() {
		static int frameCount = 0;
		static float lastTime = 0.0f;
		float currentTime = (float)glfwGetTime();

		frameCount++;

		if (currentTime - lastTime >= 1.0f) {
			FPS = (float)frameCount;
			frameCount = 0;
			lastTime = currentTime;
		}
	}

	void Renderer::processSceneDragging() {
		static bool pressing = false;
		static double lastX, lastY;

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_3) == GLFW_RELEASE)
			pressing = false;

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_3) == GLFW_PRESS && !pressing) {
			pressing = true;
			glfwGetCursorPos(window, &lastX, &lastY);
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_3) == GLFW_PRESS && pressing) {
			double xPos, yPos;
			float xoffset, yoffset;

			glfwGetCursorPos(window, &xPos, &yPos);

			xoffset = float(xPos - lastX);
			yoffset = float(yPos - lastY);
			xoffset *= midButtonSpeed * deltaTime;
			yoffset *= midButtonSpeed * deltaTime;

			lastX = xPos;
			lastY = yPos;

			mainScene.camera.processMidButtonMovement(xoffset, yoffset);
		}
	}
}