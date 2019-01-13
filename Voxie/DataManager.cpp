#include "DataManager.h"

namespace Voxie {
	DataManager::DataManager() {}

	bool DataManager::init(Scene& scene) {
		return true;
	}

	void DataManager::addVoxel(Scene& scene, glm::vec3 position, glm::vec3 color) {
		std::cout << "Add at " << getVec3String(position) << std::endl;
		scene.voxels.push_back(Voxel(position, color));
		scene.updateVoxels();
		
	}

	void DataManager::deleteVoxel(Scene& scene, int index) {
		if (scene.voxels.size() != 0) {
			std::cout << "Delete at " << getVec3String(scene.voxels[index].Position) << std::endl;
			scene.voxels.erase(scene.voxels.begin() + index);
			scene.updateVoxels();
		}
	}
}