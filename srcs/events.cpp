#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scopm.hpp>

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

    if ( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS )
		camera.ProcessKeyboard( FORWARD, 1.0f/60.0f );
    if ( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS )
		camera.ProcessKeyboard( BACKWARD, 1.0f/60.0f );
    if ( glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS )
		camera.ProcessKeyboard( LEFT, 1.0f/60.0f );
    if ( glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS )
		camera.ProcessKeyboard( RIGHT, 1.0f/60.0f );
    if ( glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS )
		camera.ProcessKeyboard( UP, 1.0f/60.0f );
    if ( glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS )
		camera.ProcessKeyboard( DOWN, 1.0f/60.0f );
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	(void)window;
	// if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top

		camera.ProcessMouseMovement( xoffset, yoffset );
	// }
	lastX = xpos;
	lastY = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	(void)window;
	(void)xoffset;
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
