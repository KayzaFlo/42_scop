#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scopm.hpp>

#include <iostream>

#include "Shader.hpp"

void		framebuffer_size_callback(GLFWwindow* window, int width, int height);
void		keypressed_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void		setupVertices( uint32_t *VBO, uint32_t *VAO, uint32_t *EBO );
void		setupTex( uint32_t * );

Matrix4x4	transform;
double		timeElpased = 0;

// current step : https://learnopengl.com/Getting-started/Hello-Triangle

GLFWwindow*	setupLibs() {
	glfwInitHint (GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);	// for MacOS, otherwise cd automatically to "Contents/Resources"
	if (!glfwInit())
		throw std::runtime_error("failed to initialize GLFW");

	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);			// version X.?  >> latest supported 4.1 on MacOS
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);			// version ?.X
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// for MacOS
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//Use core-profile (get access to a smaller subset of OpenGL features without backwards-compatible features we no longer need)

	GLFWwindow*	window = glfwCreateWindow(640, 480, "42_scop", NULL, NULL);
	if (!window)
		throw std::runtime_error("failed to create GLFW window");

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("failed to initialize GLAD");

	return window;
}

void	render( GLFWwindow *window, Shader shader, uint32_t VAO, uint32_t texture ) {
	(void)texture;
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// uniformColor shader
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	shader.setUniform("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

	transform = Matrix4x4::identity;
	transform = Matrix4x4::Translate( transform, Vector3( 0.5, 0. , 0. ) );
	transform = Matrix4x4::Rotate( transform, (float)glfwGetTime(), Vector3( 0, 0, 1 ) );
	transform = Matrix4x4::Scale( transform, Vector3( 1 / (float)glfwGetTime(), 1 / (float)glfwGetTime(), 1. ) );
	timeElpased++;
	std::cout << transform << std::endl;
	shader.setUniform("transform", transform);

	// shader.use(); // If const : not necessary to call every frame

	// bind Texture
	// glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);	// Render this iteration buffer
	glfwPollEvents();	// Check if any events are triggered andd call correspind functions / callbacks
}

int main()
{
	std::cout << "START" << std::endl;
	GLFWwindow*	window;
	try {
		window = setupLibs();
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		return -1;
	}
	Shader		shader( "srcs/shaders/texture.vs", "srcs/shaders/texture.fs" );
	std::cout << shader.ID << std::endl;
	
	// On Resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keypressed_callback);

	uint32_t	VBO, VAO, EBO;
	setupVertices( &VBO, &VAO, &EBO );
	uint32_t	texture;
	setupTex( &texture );
	// bind Texture
	// glBindTexture(GL_TEXTURE_2D, texture);

	// Render Loop
	std::cout << "LOOP" << std::endl;
	shader.use();
	while (!glfwWindowShouldClose(window))
		render( window, shader, VAO, texture );
	
	// Terminate
	std::cout << "TERMINATE" << std::endl;
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader.ID);

	glfwTerminate();


	return 0;
}
