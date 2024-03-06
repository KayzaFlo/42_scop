#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	(void)window;
	glViewport(0, 0, width, height);
	std::cout << "w: " << width << " - h: " << height << std::endl;
} 

int main()
{
	std::cout << "START" << std::endl;
	if (!glfwInit()) {
		std::cout << "failed to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);			// version X.?  >> latest supported 4.1 on MacOS
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);			// version ?.X
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// for MacOS
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//Use core-profile (get access to a smaller subset of OpenGL features without backwards-compatible features we no longer need)

	GLFWwindow* window = glfwCreateWindow(640, 480, "42_scop", NULL, NULL);
	if (!window) {
		std::cout << "failed to create GLFW window" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to initialize GLAD" << std::endl;
		return -1;
	}

	// On Resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Render Loop
	std::cout << "LOOP" << std::endl;
	while (!glfwWindowShouldClose(window)) 	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(0);
		glfwSwapBuffers(window);	// Render this iteration buffer
		glfwPollEvents();	// Check if any events are triggered andd call correspind functions / callbacks
	}
	
	// Terminate
	std::cout << "TERMINATE" << std::endl;
	glfwTerminate();
	return 0;
}
