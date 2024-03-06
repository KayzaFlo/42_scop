#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

#include <iostream>


int main()
{
	std::cout << "START" << std::endl;
	if (!glfwInit())
		return 1;

	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "42_scop", NULL, NULL);
	if (!window)
		return 1;

	glfwMakeContextCurrent(window);

	std::cout << "LOOP" << std::endl;
	while (!glfwWindowShouldClose(window)) 	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	

	std::cout << "TERMINATE" << std::endl;
	glfwTerminate();
	return 0;
}
