#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Global.h"
#include "Camera.h"

namespace Voxie {
	class BoundingBox {
	public:
		glm::vec3 bounds[2];
		static float intersectionThreshold;

		BoundingBox(glm::vec3 bound0, glm::vec3 bound1);
		bool intersect(const Camera& camera, const glm::vec3& inverseRay, float& distance);
		Direction detectIntersectionFace(const Camera& camera, const glm::vec3& ray, const float& distance);
	};
}

#endif