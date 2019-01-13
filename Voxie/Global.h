#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <glm\glm.hpp>
#include <glm\gtc/matrix_transform.hpp>
#include <glm\gtc/type_ptr.hpp>

#include <glad/glad.h>

namespace Voxie {
	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;

	const float MAX_DISTANCE = 10000.0f;

	enum Direction {
		NONE,
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	static std::string getVec3String(glm::vec3 vec) {
		std::stringstream out;
		out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return out.str();
	}

	static void log(std::string name = "log", std::string value = "test") {
		std::cout << name << ": " << value << std::endl;
	}

	static glm::vec3 getDirectionVector(Direction direction) {
		switch (direction) {
		case Voxie::NONE:
			return glm::vec3(0.0f, 0.0f, 0.0f);
		case Voxie::FORWARD:
			return glm::vec3(0.0f, 0.0f, -1.0f);
		case Voxie::BACKWARD:
			return glm::vec3(0.0f, 0.0f, 1.0f);
		case Voxie::LEFT:
			return glm::vec3(-1.0f, 0.0f, 0.0f);
		case Voxie::RIGHT:
			return glm::vec3(1.0f, 0.0f, 0.0f);
		case Voxie::UP:
			return glm::vec3(0.0f, 1.0f, 0.0f);
		case Voxie::DOWN:
			return glm::vec3(0.0f, -1.0f, 0.0f);
		default:
			throw std::runtime_error("Direction error!");
		}
	}
}

#endif