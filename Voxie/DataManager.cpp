#include "DataManager.h"

namespace Voxie {
	DataManager::DataManager() {
		currentColor = glm::vec3(1.0f, 1.0f, 1.0f);
		currentVoxel = nullptr;
	}

	bool DataManager::init(Scene& scene) {
		return true;
	}

	void DataManager::addVoxel(Scene& scene, glm::vec3 position) {
		std::cout << "Add at " << getVec3String(position) << std::endl;
		scene.voxels.push_back(Voxel(position, currentColor));
		scene.updateVoxels();
		currentVoxel = &scene.voxels.back();
	}

	void DataManager::deleteVoxel(Scene& scene, int index) {
		if (scene.voxels.size() != 0) {
			std::cout << "Delete at " << getVec3String(scene.voxels[index].Position) << std::endl;
			scene.voxels.erase(scene.voxels.begin() + index);
			scene.updateVoxels();
			currentVoxel = nullptr;
		}
	}
}