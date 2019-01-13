#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "Global.h"
#include "Scene.h"
#include "Voxel.h"

namespace Voxie {
	class DataManager {
	public:
		DataManager();

		bool init(Scene& scene);

		void addVoxel(Scene& scene, glm::vec3 position, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
		void deleteVoxel(Scene& scene, int index);
	};
}

#endif