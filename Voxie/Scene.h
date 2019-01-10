#ifndef SCENE_H
#define SCENE_H

#include "Global.h"
#include "Voxel.h"
#include "Shader.h"
#include "Camera.h"

namespace Voxie {

	struct MVPMatrix {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
	};

	class Scene {
	public:
		std::vector<Voxel> voxels;
		Shader shader;
		Camera camera;
		unsigned int VAO, VBO;
		MVPMatrix mvpMatrix;

		Scene();
		void init();
		void setup();
		void render(float width, float height);
		void updateMVPMatrix(float width, float height);
	};
}

#endif