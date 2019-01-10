#include "Renderer.h"

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
		renderer->mainScene.camera.changeZoom(yoffset >= 0 ? FORWARD : BACKWARD, abs(yoffset));
	}
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	}

	Renderer::Renderer() {
		guiManager.renderer = this;
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

	bool Renderer::render() {
		// calculate delta time
		float currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;
		updateFPS();

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// setup components
		if (guiManager.setup(window))
			glfwSetWindowShouldClose(window, true);
		mainScene.setup();

		processSceneDragging();

		// render components
		mainScene.render(scr_width, scr_height);
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
		float currentTime = glfwGetTime();

		frameCount++;

		if (currentTime - lastTime >= 1.0f) {
			FPS = frameCount;
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

			xoffset = xPos - lastX;
			yoffset = yPos - lastY;
			xoffset *= midButtonSpeed * deltaTime;
			yoffset *= midButtonSpeed * deltaTime;

			lastX = xPos;
			lastY = yPos;

			mainScene.camera.processMidButtonMovement(xoffset, yoffset);
		}
	}
}