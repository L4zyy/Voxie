#include "Scene.h"

namespace Voxie {
	Scene::Scene() {
		editMode = false;
	}

	void Scene::init() {
		shader.init("shaders/basicShader.vert", "shaders/basicShader.frag", "shaders/basicShader.geom");

		// load base voxel
		voxels.push_back(Voxel(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, voxels.size() * sizeof(Voxel), &voxels[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Voxel), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Voxel), (void*)offsetof(Voxel, Color));
		glBindVertexArray(0);
	}

	void Scene::setup(int width, int height) {
		updateVPMatrix(width, height);
	}

	void Scene::updateVoxels() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, voxels.size() * sizeof(Voxel), &voxels[0], GL_STATIC_DRAW);
	}

	void Scene::render() {
		shader.use();

		shader.setMat4("view", vpMatrix.view);
		shader.setMat4("projection", vpMatrix.projection);

		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, voxels.size());
	}

	void Scene::updateVPMatrix(int width, int height) {
		vpMatrix.view = camera.GetViewMatrix();
		vpMatrix.projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
	}
}
