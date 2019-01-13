#ifndef SCENE_H
#define SCENE_H

#include "Global.h"
#include "Voxel.h"
#include "Shader.h"
#include "Camera.h"

namespace Voxie {

	struct VPMatrix {
		glm::mat4 view;
		glm::mat4 projection;
	};

	class Scene {
	public:
		std::vector<Voxel> voxels;

		Shader shader;
		Camera camera;
		unsigned int VAO, VBO;
		VPMatrix vpMatrix;

		Scene();
		void init();
		void setup(int width, int height);
		void updateVoxels();
		void render();
		void updateVPMatrix(int width, int height);
	};
}

#endif