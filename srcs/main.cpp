#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scopm.hpp>

#include <iostream>

#include "Shader.hpp"
#include "Mesh.hpp"
#include "Model.hpp"

s_Vector2	horizontalAxis = {};
s_Vector2	verticalAxis = {};
s_Vector2	zAxis = {};

void		framebuffer_size_callback(GLFWwindow* window, int width, int height);
void		keypressed_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void		mouse_callback(GLFWwindow* window, double xpos, double ypos);
void		scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Camera	camera(Vector3(0.0f, 1.8f, 6.0f));

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

void	render( GLFWwindow *window, Shader *shader, Model *obj ) {

	camera.Move(horizontalAxis, verticalAxis, zAxis, 1.0f/60.0f);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// uniformColor shader
	// float timeValue = glfwGetTime();
	// float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	// shader.setUniform("ourColor", 0.0f, greenValue, 0.0f, 1.0f);


	int w, h;
	glfwGetWindowSize(window, &w, &h);

	
	Matrix4x4	view = camera.GetViewMatrix();
	Matrix4x4	projection = Matrix4x4::Perspective(radians(camera.zoom), (float)w/(float)h, 0.1f, 100);
	shader->setUniform("view", view);
	shader->setUniform("projection", projection);
	shader->setUniform("viewPos", camera.position.x, camera.position.y, camera.position.z);

	Matrix4x4	model = Matrix4x4::identity;
	model = Matrix4x4::Rotate(model, 0, Vector3(1,0,0));
	model = Matrix4x4::Rotate(model, (float)glfwGetTime()/2, Vector3(0, 1, 0).normalized());
	obj->transform = model;
	obj->Draw();

	glfwSwapBuffers(window);	// Render this iteration buffer
	glfwPollEvents();	// Check if any events are triggered andd call correspind functions / callbacks
}

int main( int argc, char **argv )
{
	// horizontalAxis = {};
	// verticalAxis = {};
	// zAxis = {};

	if ( argc != 3 )
		return 1;

	// std::cout << "START" << std::endl;
	GLFWwindow*	window;
	try {
		window = setupLibs();
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		return -1;
	}
	std::string	vsPath = "srcs/shaders/" + std::string(argv[2]) + ".vs";
	std::string	fsPath = "srcs/shaders/" + std::string(argv[2]) + ".fs";
	Shader *	shader = new Shader( vsPath.c_str(), fsPath.c_str() );
	
	// On Resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keypressed_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
	glfwSetScrollCallback(window, scroll_callback);

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    // stbi_set_flip_vertically_on_load(true);

	glEnable(GL_DEPTH_TEST);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Load Model
	Model *	model =  new Model(argv[1], shader);

	// Render Loop
	while (!glfwWindowShouldClose(window))
		render( window, shader, model );
	
	// Terminate
	glfwTerminate();

	delete(shader);
	delete(model);

	return 0;
}
