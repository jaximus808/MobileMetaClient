#include"Camera.h"

Camera::Camera(int width, int height, glm::vec3 position, GLFWwindow* _window)
{
	Camera::width = width; 
	Camera::height = height; 
	Position = position;
	window = _window;
	glfwSetCursorPos(window, width / 2, height / 2);
	
}


void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	//glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));

	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(float deltaTime)
{	

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed* deltaTime * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * deltaTime *-glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * deltaTime * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * deltaTime * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * deltaTime * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * deltaTime * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.4f;
	}


	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{

		focused = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetCursorPos(window, width / 2, height / 2);
		focused = true; 
	}
	if (focused)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (height / 2)) / width;

		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));
		if (!(glm::angle(newOrientation, Up) <= glm::radians(5.0f) || glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))
		{
			Orientation = newOrientation;
		}

		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		glfwSetCursorPos(window, width / 2, height / 2);
	}

	
	

}