#include "Character.h"

	Character::Character(const std::string name, float size, glm::vec3 position, float rotationSpeed, float speed, std::string direction)
	{
		this->name = name;
		characterModel = new ObjModel("models/steve/Steve.obj");
		this->size = size;
		this->position = position;
		this->rotationSpeed = rotationSpeed;
		this->speed = speed;
		this->direction = direction;
	}

	Character::~Character()
	{
		delete characterModel;
	}

	void Character::jump()
	{
		position.y = 0.65f;
	}

	void Character::duck()
	{
		rotationVector = glm::vec3(0, 0, 1);
		rotation = 0.9f;
	}

	void Character::stand()
	{
		position.y = 0.25f;
		rotation = 0;
	}

	void Character::update()
	{
		rotation += rotationSpeed;

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
		matrix = glm::rotate(matrix, rotation, rotationVector);
		matrix = glm::scale(matrix, glm::vec3((0.25f) * size));

		tigl::shader->setModelMatrix(matrix);

		characterModel->draw();
	}