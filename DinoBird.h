#pragma once
#include "ObjModel.h"
#include <GL/glew.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"

class DinoBird: public Object {
private:

public:
	ObjModel* characterModel;
	float size;
	glm::vec3 position;
	float rotation = (-0.5 * 3.14159265359);
	float rotationSpeed;
	float speed;
	std::string direction;

	DinoBird(const std::string name, float size, glm::vec3 position, float rotationSpeed, float speed, std::string direction);
	~DinoBird();
	void update();
	void draw();
};