#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "Global.h"
#include "Scene.h"
#include "Voxel.h"

namespace Voxie {
	class DataManager {
	public:
		Voxel* currentVoxel;
		glm::vec3 currentColor;

		DataManager();

		bool init(Scene& scene);

		void addVoxel(Scene& scene, glm::vec3 position);
		void deleteVoxel(Scene& scene, int index);
	};
}

#endif