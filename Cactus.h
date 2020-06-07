#pragma once
#include "ObjModel.h"
#include <GL/glew.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

class Cactus {
private:

public:
	ObjModel* characterModel;
	float size;
	glm::vec3 position;
	float rotation;
	float rotationSpeed;
	float speed;
	std::string direction;

	void createCactus(const std::string name, float size, glm::vec3 position, float rotationSpeed, float speed, std::string direction);
	void update();
	void draw();
};