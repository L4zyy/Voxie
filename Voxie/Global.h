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

	enum Direction {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
}

#endif