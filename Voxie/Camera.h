#ifndef CAMERA_H
#define CAMERA_H

#include "Global.h"

namespace Voxie {
	// default values
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float ZOOM = 45.0f;

	class Camera {
	public:
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;

		float Yaw;
		float Pitch;
		float Zoom;

		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw = YAW, float pitch = PITCH);

		glm::mat4 GetViewMatrix();
		void changePosition(Direction direction, float offset);
		void changeDirection(Direction direction, float offset, GLboolean constrainPitch = true);
		void changeZoom(Direction direction, float offset);
		void processMidButtonMovement(float xoffset, float yoffset);

	private:
		void updateCameraVectors();
	};
}

#endif