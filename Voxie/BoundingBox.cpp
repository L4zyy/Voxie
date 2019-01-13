#include "BoundingBox.h"

namespace Voxie {
	float BoundingBox::intersectionThreshold = 0.001f; // higher precision will cause face detaction return NONE

	BoundingBox::BoundingBox(glm::vec3 bound0, glm::vec3 bound1) {
		bounds[0] = bound0;
		bounds[1] = bound1;
	}

	bool BoundingBox::intersect(const Camera& camera, const glm::vec3& inverseRay, float& distance) {
		int sign[3] = { inverseRay.x < 0, inverseRay.y < 0, inverseRay.z < 0 };
		float tmin, tmax, tymin, tymax, tzmin, tzmax;
		tmin = (bounds[sign[0]].x - camera.Position.x) * inverseRay.x;
		tmax = (bounds[1 - sign[0]].x - camera.Position.x) * inverseRay.x;
		tymin = (bounds[sign[1]].y - camera.Position.y) * inverseRay.y;
		tymax = (bounds[1 - sign[1]].y - camera.Position.y) * inverseRay.y;

		if ((tmin > tymax) || (tmax < tymin))
			return false;
		if (tymin > tmin)
			tmin = tymin;
		if (tymax < tmax)
			tmax = tymax;

		tzmin = (bounds[sign[2]].z - camera.Position.z) * inverseRay.z;
		tzmax = (bounds[1 - sign[2]].z - camera.Position.z) * inverseRay.z;

		if ((tmin > tzmax) || (tmax < tzmin))
			return false;
		if (tzmin > tmin)
			tmin = tzmin;
		if (tzmax < tmax)
			tmax = tzmax;

		distance = tmin;

		return true;
	}

	Direction BoundingBox::detectIntersectionFace(const Camera& camera, const glm::vec3& ray, const float& distance) {
		glm::vec3 point = camera.Position + (distance * ray);
		if (abs(point.x - bounds[0].x) < intersectionThreshold)
			return LEFT;
		if (abs(point.y - bounds[0].y) < intersectionThreshold)
			return DOWN;
		if (abs(point.z - bounds[0].z) < intersectionThreshold)
			return FORWARD;
		if (abs(point.x - bounds[1].x) < intersectionThreshold)
			return RIGHT;
		if (abs(point.y - bounds[1].y) < intersectionThreshold)
			return UP;
		if (abs(point.z - bounds[1].z) < intersectionThreshold)
			return BACKWARD;

		return NONE;
	}
}