#pragma once
#include "ObjModel.h"
#include <GL/glew.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

class Object {
private:

public:
	std::string name;

	virtual void update();
	virtual void draw();
};