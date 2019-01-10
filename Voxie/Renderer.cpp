#include "Renderer.h"

namespace Voxie {
	// variables
	float deltaTime = 0.0f;
	float lastFrameTime = 0.0f;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		Renderer* renderer = reinterpret_cast<Renderer*>(glfwGetWindowUserPointer(window));
		renderer->scr_width = width;
		renderer->scr_height = height;
	}

	void processInput(GLFWwindow* window, Scene& scene) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			scene.camera.ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			scene.camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			scene.camera.ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			scene.camera.ProcessKeyboard(RIGHT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			scene.camera.ProcessKeyboard(UP, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			scene.camera.ProcessKeyboard(DOWN, deltaTime);
	}

	Renderer::Renderer() {
		guiManager.renderer = this;
		scr_width = SCR_WIDTH;
		scr_height = SCR_HEIGHT;
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
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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

		return true;
	}

	bool Renderer::render() {
		// calculate delta time
		float currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;
		updateFPS();

		// process input
		processInput(window, mainScene);

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// setup components
		if (guiManager.setup(window))
			glfwSetWindowShouldClose(window, true);
		mainScene.setup();

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
}