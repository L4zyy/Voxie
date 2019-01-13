#ifndef MOUSEPICKER_H
#define MOUSEPICKER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Global.h"

namespace Voxie {
	class MousePicker {
	public:
		MousePicker();

		bool init(GLFWwindow* w);
		void update(glm::mat4 viewMat, glm::mat4 projectionMat);

		glm::vec3 getCurrentRay();
	private:
		GLFWwindow* window;

		glm::vec3 currentRay;
		glm::mat4 projection;
		glm::mat4 view;

		glm::vec3 calculateMouseRay();
		glm::vec2 getNormalizedDeviceCoords(double mouseX, double mouseY);
		glm::vec4 toEyeCoords(glm::vec4 clipCoords);
		glm::vec3 toWorldCoords(glm::vec4 eyeCoords);
	};
}

#endif