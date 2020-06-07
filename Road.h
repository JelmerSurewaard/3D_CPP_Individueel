#pragma once
#include "ObjModel.h"
#include <GL/glew.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"

class Road: public Object {
private:

public:
	ObjModel* characterModel;
	float size;
	glm::vec3 position;

	Road(const std::string name, float size, glm::vec3 position);
	~Road();
	void update();
	void draw();
};