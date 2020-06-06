#include "Character.h"

	void Character::createCharacter(const std::string name, float size, glm::vec3 position, float rotationSpeed, float speed, std::string direction)
	{

		characterModel = new ObjModel("models/steve/Steve.obj");
		this->size = size;
		this->position = position;
		this->rotationSpeed = rotationSpeed;
		this->speed = speed;
		this->direction = direction;
	}

	void Character::update()
	{
		rotation += rotationSpeed;
		// update direction

		if (direction == "x")
		{
			position = glm::vec3(position.x + (1 * speed), position.y, position.z);
		}
		if (direction == "y")
		{
			position = glm::vec3(position.x, position.y + (1 * speed), position.z);
		}
		if (direction == "z")
		{
			position = glm::vec3(position.x, position.y, position.z + (1 * speed));
		}

	}

	void Character::draw() 
	{
		glm::mat4 matrix = glm::mat4(1.0f);
		matrix = glm::translate(matrix, position);
		matrix = glm::rotate(matrix, rotation, glm::vec3(0, 1, 0));
		matrix = glm::scale(matrix, glm::vec3((0.25f) * size));

		tigl::shader->setModelMatrix(matrix);

		characterModel->draw();
	}