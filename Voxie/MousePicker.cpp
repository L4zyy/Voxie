#include "MousePicker.h"

namespace Voxie {
	MousePicker::MousePicker() {}

	bool MousePicker::init(GLFWwindow* w) {
		window = w;

		return true;
	}
	void MousePicker::update(glm::mat4 viewMat, glm::mat4 projectionMat) {
		view = viewMat;
		projection = projectionMat;
		currentRay = calculateMouseRay();
	}

	glm::vec3 MousePicker::getCurrentRay() {
		return currentRay;
	}

	glm::vec3 MousePicker::calculateMouseRay() {
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		glm::vec2 normalizedCoords = getNormalizedDeviceCoords(mouseX, mouseY);
		glm::vec4 clipCoords = glm::vec4(normalizedCoords, -1.0f, 1.0f);
		glm::vec4 eyeCoords = toEyeCoords(clipCoords);

		return toWorldCoords(eyeCoords);
	}
	glm::vec2 MousePicker::getNormalizedDeviceCoords(double mouseX, double mouseY) {
		int windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		float x = (2.0f * mouseX) / windowWidth - 1;
		float y = (2.0f * mouseY) / windowHeight - 1;
		y *= -1.0f;	// using negative y because of the orign starts at left top corner
		return glm::vec2(x, y);
	}
	glm::vec4 MousePicker::toEyeCoords(glm::vec4 clipCoords) {
		glm::vec4 eyeCoords = glm::inverse(projection) * clipCoords;
		return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
	}
	glm::vec3 MousePicker::toWorldCoords(glm::vec4 eyeCoords) {
		glm::vec4 worldCoords = glm::inverse(view) * eyeCoords;
		glm::vec3 mouseRay = glm::vec3(worldCoords.x, worldCoords.y, worldCoords.z);
		return glm::normalize(mouseRay);
	}
}