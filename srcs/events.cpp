#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scopm.hpp>
#include "scop.h"

#include <iostream>

float	lastX, lastY;
bool	firstMouse = true;

void	framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	(void)window;
	glViewport(0, 0, width, height);
	// std::cout << "w: " << width << " - h: " << height << std::endl;
}

void	processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	// Quit with Escape key
		glfwSetWindowShouldClose(window, true);
}

void keypressed_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	(void)scancode;
	(void)action;
	(void)mods;
	// std::cout << "key: " << key << " - scancode: " << scancode << " - action: " << action << " - mods: " << mods << std::endl;
	if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )	// Quit with Escape key
		glfwSetWindowShouldClose(window, true);

	if( key == GLFW_KEY_F && action == GLFW_PRESS )	{
		needShaderUpdate = 1;
		currentShaderId++;
	}
		
    if ( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS )
		verticalAxis.x = 1;
    if ( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS )
		verticalAxis.y = 1;
    if ( glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS )
		horizontalAxis.x = 1;
    if ( glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS )
		horizontalAxis.y = 1;
    if ( glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS )
		zAxis.x = 1;
    if ( glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS )
		zAxis.y = 1;

    if ( glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE )
		verticalAxis.x = 0;
    if ( glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE )
		verticalAxis.y = 0;
    if ( glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE )
		horizontalAxis.x = 0;
    if ( glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE )
		horizontalAxis.y = 0;
    if ( glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE )
		zAxis.x = 0;
    if ( glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE )
		zAxis.y = 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	(void)window;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top

		camera.ProcessMouseMovement( xoffset, yoffset );
	}
	lastX = xpos;
	lastY = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	(void)window;
	(void)xoffset;
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
