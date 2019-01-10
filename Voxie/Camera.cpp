#include "Camera.h"

namespace Voxie {
	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), Zoom(ZOOM) {
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), Zoom(ZOOM) {
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	glm::mat4 Camera::GetViewMatrix() {
		return glm::lookAt(Position, Position + Front, Up);
	}

	void Camera::changePosition(Direction direction, float offset) {
		if (direction == FORWARD)
			Position += Front * offset;
		if (direction == BACKWARD)
			Position -= Front * offset;
		if (direction == LEFT)
			Position -= Right * offset;
		if (direction == RIGHT)
			Position += Right * offset;
		if (direction == UP)
			Position += WorldUp * offset;
		if (direction == DOWN)
			Position -= WorldUp * offset;
	}

	void Camera::changeDirection(Direction direction, float offset, GLboolean constrainPitch) {
		if (direction == UP)
			Pitch += offset;
		else if (direction == DOWN)
			Pitch -= offset;
		else if (direction == LEFT)
			Yaw -= offset;
		else if (direction == RIGHT)
			Yaw += offset;

		if (constrainPitch) {
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void Camera::changeZoom(Direction direction, float offset) {
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			if (direction == FORWARD)
				Zoom -= offset;
			else if (direction == BACKWARD)
				Zoom += offset;

		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}

	void Camera::updateCameraVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
		front.y = sin(glm::radians(Pitch));
		front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));

		Front = glm::normalize(front);
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
}
