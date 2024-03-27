#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scopm.hpp>

#include <iostream>

#include "Shader.hpp"

#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080

void		framebuffer_size_callback(GLFWwindow* window, int width, int height);
void		keypressed_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void		setupVertices( uint32_t *VBO, uint32_t *VAO, uint32_t *EBO );
void		setupTex( uint32_t * );

Matrix4x4	transform;
double		timeElpased = 0;

Vector3 cubePositions[] = {
    Vector3( 0.0f,  0.0f,  0.0f),
    Vector3( 2.0f,  5.0f, -15.0f),
    Vector3(-1.5f, -2.2f, -2.5f),
    Vector3(-3.8f, -2.0f, -12.3f),
    Vector3( 2.4f, -0.4f, -3.5f),
    Vector3(-1.7f,  3.0f, -7.5f),
    Vector3( 1.3f, -2.0f, -2.5f),
    Vector3( 1.5f,  2.0f, -2.5f),
    Vector3( 1.5f,  0.2f, -1.5f),
    Vector3(-1.3f,  1.0f, -1.5f) 
};

// current step : https://learnopengl.com/Getting-started/Hello-Triangle

GLFWwindow*	setupLibs() {
	glfwInitHint (GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);	// for MacOS, otherwise cd automatically to "Contents/Resources"
	if (!glfwInit())
		throw std::runtime_error("failed to initialize GLFW");

	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);			// version X.?  >> latest supported 4.1 on MacOS
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);			// version ?.X
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// for MacOS
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//Use core-profile (get access to a smaller subset of OpenGL features without backwards-compatible features we no longer need)

	GLFWwindow*	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "42_scop", NULL, NULL);
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
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// uniformColor shader
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	shader.setUniform("ourColor", 0.0f, greenValue, 0.0f, 1.0f);


	int w, h;
	glfwGetWindowSize(window, &w, &h);

	Matrix4x4	model = Matrix4x4::Rotate(Matrix4x4::identity, -0.96, Vector3(1,0,0));
	model = Matrix4x4::Rotate(model, (float)glfwGetTime()/2, Vector3(0.5, 1, 1).normalized());
	Matrix4x4	view = Matrix4x4::Translate(Matrix4x4::identity, Vector3(0,0,-5));
	Matrix4x4	projection = Matrix4x4::Perspective(0.785f, (float)w/(float)h, 0.1f, 100);
	shader.setUniform("model", model);
	std::cout << "model:\n" << model;
	shader.setUniform("view", view);
	std::cout << "view:\n" << view;
	shader.setUniform("projection", projection);
	std::cout << "projection:\n" << projection;

	// transform = Matrix4x4::identity;
	// transform = Matrix4x4::Translate( transform, Vector3( 0.5, -0.5, 0. ) );
	// transform = Matrix4x4::Rotate( transform, (float)glfwGetTime(), Vector3( 0, 0, 1 ) );
	// transform = Matrix4x4::Scale( transform, Vector3( 1 / (float)glfwGetTime(), 1 / (float)glfwGetTime(), 1. ) );
	// timeElpased++;
	// std::cout << transform;
	// shader.setUniform("transform", transform);

	// shader.use(); // If const : not necessary to call every frame

	// bind Texture
	// glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);
	for(unsigned int i = 0; i < 10; i++)
	{
		model = Matrix4x4::Translate(Matrix4x4::identity, cubePositions[i]);
		float angle = 20.0f * i;
		if ( i % 3 == 0 )
			model = Matrix4x4::Rotate(model, angle * (M_PI/180) + (float)glfwGetTime() / 5, Vector3(1.0f, 0.3f, 0.5f));
		else
			model = Matrix4x4::Rotate(model, angle * (M_PI/180), Vector3(1.0f, 0.3f, 0.5f));
		shader.setUniform("model", model);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // use EBO
		// glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // use EBO
	// glDrawArrays(GL_TRIANGLES, 0, 36); // without EBO / faces



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
