#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define INC_DEC_VALUE_RADIUS .07
#define INC_DEC_VALUE_ROTATIONX .0095
#define INC_DEC_VALUE_ROTATIONY .025

constexpr auto PI = 3.14159265359;

struct GLFWwindow;

class Camera
{
public:
	Camera(GLFWwindow*);
	glm::mat4 getMatrix();
	void updateKeyInput(GLFWwindow*);
	void checkTargetRadius();
	void checkTargetRotation();
	void setStartGamePosition();
	glm::vec3 translation = glm::vec3(0, 0, 0);
	double targetRadius = -1;
	glm::vec3 targetRotation = glm::vec3(-1, -1, -1);
	double rotY = 0;
	double radius = 10;
	bool player1Cam = true;

	int arrowUp = 0;
	int arrowDown = 0;
private:
	glm::vec3 position = glm::vec3(4, -1, 0);
	glm::vec3 rotation = glm::vec3(0.5f, 0.5 * PI, 0);
	void move(float angle, float fac);
	int speed = 1;
};