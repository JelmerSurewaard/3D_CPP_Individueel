#include "Road.h"

Road::Road(const std::string name, float size, glm::vec3 position)
{
	this->name = name;
	characterModel = new ObjModel("models/road/road.obj");
	this->size = size;
	this->position = position;
}

Road::~Road()
{
	delete characterModel;
}

void Road::update()
{

}

void Road::draw()
{
	glm::mat4 matrix = glm::mat4(1.0f);
	
	matrix = glm::scale(matrix, glm::vec3((0.25f) * size));

	tigl::shader->setModelMatrix(matrix);

	characterModel->draw();
}