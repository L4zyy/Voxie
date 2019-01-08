#ifndef VOXEL_H
#define VOXEL_H

#include "Global.h"

class Voxel {
public:
	glm::vec3 Position;
	glm::vec3 Color;

	Voxel(glm::vec3 position, glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f));
};

#endif