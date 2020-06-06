#include "Character.h"

	void Character::createCharacter(const std::string name, int size, glm::vec3 position, float rotation, float speed, const std::string direction)
	{

		characterModel = new ObjModel("models/steve/Steve.obj");
		this->size = size;
		this->position = position;
		this->rotation = rotation;
		this->speed = speed;
		this->direction == direction;
	}

	void Character::update()
	{
		//rotation += 0.01f;
		// update direction

	}

	void Character::draw() 
	{
		glm::mat4 matrix = glm::mat4(1.0f);
		matrix = glm::translate(matrix, position);
		matrix = glm::rotate(matrix, rotation, glm::vec3(0, 1, 0));
		matrix = glm::scale(matrix, glm::vec3(0.25f));

		tigl::shader->setModelMatrix(matrix);

		characterModel->draw();
	}