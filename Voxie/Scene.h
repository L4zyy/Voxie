#ifndef SCENE_H
#define SCENE_H

#include "Global.h"
#include "Voxel.h"
#include "Shader.h"
#include "Camera.h"

namespace Voxie {

	static const float DEFAULT_BORDER_WIDTH = 0.08f;

	struct VPMatrix {
		glm::mat4 view;
		glm::mat4 projection;
	};

	struct BorderInfo {
		float width;
		glm::vec3 color;
	};

	class Scene {
	public:
		std::vector<Voxel> voxels;

		Shader shader;
		Camera camera;
		unsigned int VAO, VBO;
		VPMatrix vpMatrix;
		BorderInfo borderInfo;

		bool editMode;
		bool showBorder;

		Scene();
		void init();
		void setup(int width, int height);
		void updateVoxels();
		void render();
		void updateVPMatrix(int width, int height);
		void updateBorderInfo(float width, glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f));
	};
}

#endif