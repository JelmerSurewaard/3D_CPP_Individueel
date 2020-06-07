#pragma once
#include "ObjModel.h"
#include <GL/glew.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

class Road {
private:

public:
	ObjModel* characterModel;
	float size;
	glm::vec3 position;

	void createRoad(const std::string name, float size, glm::vec3 position);
	void update();
	void draw();
};