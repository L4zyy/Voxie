#include "Voxel.h"

namespace Voxie {
	Voxel::Voxel(glm::vec3 position, glm::vec3 color) : Position(position), Color(color), boundingBox(position + glm::vec3(-0.5f), position + glm::vec3(0.5f)) {}
}