#include "Scene.h"

namespace Voxie {
	Scene::Scene() : camera(glm::vec3(0.0f, 0.0f, 3.0f)) {}

	void Scene::init() {
		shader.init("shaders/basicShader.vert", "shaders/basicShader.frag", "shaders/basicShader.geom");

		float points[] = {
			0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glBindVertexArray(0);
	}

	void Scene::setup() {}

	void Scene::render() {
		shader.use();

		glm::mat4 model, view, projection;
		model = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, 1);
	}
}
