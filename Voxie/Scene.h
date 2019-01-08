#ifndef SCENE_H
#define SCENE_H

#include "Global.h"
#include "Voxel.h"
#include "Shader.h"
#include "Camera.h"

class Scene {
public:
	std::vector<Voxel> voxels;
	Shader shader;
	Camera camera;
	unsigned int VAO, VBO;

	Scene();
	void init();
	void setup();
	void render();
};

#endif