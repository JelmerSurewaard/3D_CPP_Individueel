#pragma once
#include "ObjModel.h"
#include <GL/glew.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

class Character {
private:

public:
	ObjModel* characterModel;
	int size;
	glm::vec3 position;
	float rotation;
	float speed;
	const std::string direction;

	void createCharacter(const std::string name, int size, glm::vec3 position, float rotation, float speed, const std::string direction);
	void update();
	void draw();
};