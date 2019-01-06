#ifndef VOXIE_H
#define VOXIE_H

#include <iostream>
#include <cmath>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image\stb_image.h>
#include <glm\glm.hpp>
#include <glm\gtc/matrix_transform.hpp>
#include <glm\gtc/type_ptr.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Global.h"

class Voxie {
public:
	GLFWwindow* window;

	Voxie();
	bool init();
	void mainLoop();
	void cleanup();
private:
};

#endif