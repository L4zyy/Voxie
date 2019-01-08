#include "Core.h"

namespace Voxie {
	using namespace std;

	// variables
	float deltaTime = 0.0f;
	float lastFrameTime = 0.0f;
	bool firstMouse = true;
	float lastX = SCR_WIDTH / 2, lastY = SCR_HEIGHT / 2;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
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

	Core::Core() {}

	bool Core::init() {
		// init glfw
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// create window
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Voxie", nullptr, nullptr);
		if (window == nullptr) {
			cout << "Failed to create main window" << endl;
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		// init glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			cout << "Failed to initialize GLAD" << endl;
			return false;
		}

		// init GUI
		if (!guiManager.init(window)) {
			cout << "Failed to initialize GUI" << endl;
			return false;
		}

		// init scene
		mainScene.init();

		// configure global opengl state
		glEnable(GL_DEPTH_TEST);

		return true;
	}

	void Core::mainLoop() {
		while (!glfwWindowShouldClose(window)) {
			// calculate delta time
			float currentFrameTime = glfwGetTime();
			deltaTime = currentFrameTime - lastFrameTime;
			lastFrameTime = currentFrameTime;

			// process input
			processInput(window, mainScene);

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// setup components
			if (guiManager.setup(window))
				glfwSetWindowShouldClose(window, true);
			mainScene.setup();

			// render components
			guiManager.render();
			mainScene.render();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	void Core::cleanup() {
		guiManager.cleanup();

		glfwTerminate();
	}
}
