#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scopm.hpp>

#include <iostream>

#include "Shader.hpp"
#include "Mesh.hpp"
#include "Model.hpp"

#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080

void		framebuffer_size_callback(GLFWwindow* window, int width, int height);
void		keypressed_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void		mouse_callback(GLFWwindow* window, double xpos, double ypos);
void		scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
Mesh		box();

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

Camera	camera(Vector3(0.0f, 0.0f,  3.0f));

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

void	render( GLFWwindow *window, Shader shader, Model &mesh ) {
	// (void)texture;
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// uniformColor shader
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	shader.setUniform("ourColor", 0.0f, greenValue, 0.0f, 1.0f);


	int w, h;
	glfwGetWindowSize(window, &w, &h);

	// Matrix4x4	model = Matrix4x4::identity;
	Matrix4x4	model = Matrix4x4::Rotate(Matrix4x4::identity, 0, Vector3(1,0,0));
	// model = Matrix4x4::Rotate(model, (float)glfwGetTime()/2, Vector3(0, 1, 0).normalized());
	
	shader.use(); // If const : not necessary to call every frame

	Matrix4x4	view = camera.GetViewMatrix();
	Matrix4x4	projection = Matrix4x4::Perspective(radians(camera.zoom), (float)w/(float)h, 0.1f, 100);
	shader.setUniform("model", model);
	shader.setUniform("view", view);
	shader.setUniform("projection", projection);
	// std::cout << "model:\n" << model << "view:\n" << view << "projection:\n" << projection;

	// for(unsigned int i = 0; i < 10; i++)
	// {
	// 	model = Matrix4x4::Translate(Matrix4x4::identity, cubePositions[i]);
	// 	float angle = 20.0f * i;
	// 	if ( i % 3 == 0 )
	// 		model = Matrix4x4::Rotate(model, angle * (M_PI/180) + (float)glfwGetTime() / 5, Vector3(1.0f, 0.3f, 0.5f));
	// 	else
	// 		model = Matrix4x4::Rotate(model, angle * (M_PI/180), Vector3(1.0f, 0.3f, 0.5f));
	// 	shader.setUniform("model", model);

	// 	mesh.Draw(shader);
	// }
	
		mesh.Draw(shader);
	
	// glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // use EBO
	// // glDrawArrays(GL_TRIANGLES, 0, 36); // without EBO / faces

	glfwSwapBuffers(window);	// Render this iteration buffer
	glfwPollEvents();	// Check if any events are triggered andd call correspind functions / callbacks
}

int main( int argc, char **argv )
{
	if ( argc != 3 )
		return 1;

	std::cout << "START" << std::endl;
	GLFWwindow*	window;
	try {
		window = setupLibs();
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		return -1;
	}
	std::string	vsPath = "srcs/shaders/" + std::string(argv[2]) + ".vs";
	std::string	fsPath = "srcs/shaders/" + std::string(argv[2]) + ".fs";
	Shader		shader( vsPath.c_str(), fsPath.c_str() );
	
	// On Resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keypressed_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
	glfwSetScrollCallback(window, scroll_callback);

	glEnable(GL_DEPTH_TEST);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Mesh	boxMesh = box();
	Model	model(argv[1]);

	// boxMesh.print();
	// model.meshes[0].print();

	// Render Loop
	std::cout << "LOOP" << std::endl;
	shader.use();
	while (!glfwWindowShouldClose(window))
		render( window, shader, model );
	
	// Terminate
	std::cout << "TERMINATE" << std::endl;
	glfwTerminate();

	return 0;
}
