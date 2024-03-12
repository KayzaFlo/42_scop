#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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
	std::cout << "key: " << key << " - scancode: " << scancode << " - action: " << action << " - mods: " << mods << std::endl;
	if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )	// Quit with Escape key
		glfwSetWindowShouldClose(window, true);
}
