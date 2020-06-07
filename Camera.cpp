#include "Camera.h"
static double camX;
static double camZ;
static double rotX;

Camera::Camera(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

glm::mat4 Camera::getMatrix()
{
	glm::mat4 ret(1.0f);
	ret = glm::rotate(ret, rotation.x, glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, rotation.y, glm::vec3(0, 1, 0));
	ret = glm::translate(ret, position);
	return ret;
}

void Camera::move(float angle, float fac)
{
	position.x += (float)cos(rotation.y + glm::radians(angle)) * fac;
	position.z += (float)sin(rotation.y + glm::radians(angle)) * fac;
}

void Camera::updateKeyInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move(0, 0.05f * speed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move(180, 0.05f * speed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		move(-90, 0.05f * speed);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		move(90, 0.05f * speed);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		position.y += 0.1 * speed;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		position.y -= 0.1 * speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		speed = 2;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		speed = 1;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		if (arrowUp == 0 && arrowDown == 0)
		{
			arrowUp = 100;
		}
	}	
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (arrowDown == 0 && arrowUp == 0)
		{
			arrowDown = 100;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		if (true)
		{
			this->lightning = !lightning;
		}
	}
		
	
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	static double lastX = x;
	static double lastY = y;

	rotation.x -= (float)(lastY - y) / 100.0f;
	rotation.y -= (float)(lastX - x) / 100.0f;

	lastX = x;
	lastY = y;
}

void Camera::checkTargetRadius() {
	if (this->targetRadius != -1) {
		if (radius != targetRadius) {
			std::cout << "Absolute value" << std::abs(targetRadius - radius) << std::endl;
			if (std::abs(targetRadius - radius) > INC_DEC_VALUE_RADIUS) {
				if (radius > targetRadius)
					radius -= INC_DEC_VALUE_RADIUS;
				else
					radius += INC_DEC_VALUE_RADIUS;
			}
			else targetRadius = -1;
		}
	}
}

void Camera::checkTargetRotation() {
	if (this->targetRotation.x != -1) {
		if (rotX != targetRotation.x) {
			std::cout << "Absolute value" << std::abs(targetRotation.x - rotX) << std::endl;
			if (std::abs(targetRotation.x - rotX) > INC_DEC_VALUE_ROTATIONX) {
				if (rotX > targetRotation.x)
					rotX -= INC_DEC_VALUE_ROTATIONX;
				else
					rotX += INC_DEC_VALUE_ROTATIONX;
			}
			else {
				rotX = targetRotation.x;
				targetRotation.x = -1;
			}
		}
	}

	if (this->targetRotation.y != -1) {
		if (rotY != targetRotation.y) {
			if (std::abs(targetRotation.y - rotY) > INC_DEC_VALUE_ROTATIONY) {
				if (rotY > targetRotation.y)
					rotY -= INC_DEC_VALUE_ROTATIONY;
				else
					rotY += INC_DEC_VALUE_ROTATIONY;
			}
			else {
				rotY = targetRotation.y;
				targetRotation.y = -1;
			}
		}
	}
}

void Camera::setStartGamePosition() {
	rotX = PI / 2.;
	rotY = 0;
	radius = 1.;
	this->targetRadius = 11.3;
}
