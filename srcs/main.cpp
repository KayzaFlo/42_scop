#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scopm.hpp>

#include <iostream>
#include <map>

#include "Shader.hpp"
#include "Mesh.hpp"
#include "Model.hpp"

Vec2	horizontalAxis = {};
Vec2	verticalAxis = {};
Vec2	zAxis = {};
int		currentShaderId = 0;

Camera	camera(Vec3(0.0f, 1.8f, 6.0f));

// std::map< std::string, Shader * >	shaders;
std::vector<Shader *>		shaders;

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

void	render( GLFWwindow *window, Model *obj ) {

	camera.Move(horizontalAxis, verticalAxis, zAxis, 1.0f/60.0f);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// uniformColor shader
	// float timeValue = glfwGetTime();
	// float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	// shader.setUniform("ourColor", 0.0f, greenValue, 0.0f, 1.0f);


	int w, h;
	glfwGetWindowSize(window, &w, &h);

	// shader->use();
	
	Mat4	view = camera.GetViewMatrix();
	Mat4	projection = Mat4::Perspective(radians(camera.zoom), (float)w/(float)h, 0.1f, 100);
	obj->getShader()->setUniform("view", view);
	obj->getShader()->setUniform("projection", projection);
	obj->getShader()->setUniform("viewPos", camera.position.x, camera.position.y, camera.position.z);

	Mat4	model = Mat4::identity;
	model = Mat4::Rotate(model, 0, Vec3(1,0,0));
	model = Mat4::Rotate(model, (float)glfwGetTime()/2, Vec3(0, 1, 0).normalized());
	obj->transform = model;
	obj->Draw();

	glfwSwapBuffers(window);	// Render this iteration buffer
	glfwPollEvents();	// Check if any events are triggered andd call correspind functions / callbacks
}

int main( int argc, char **argv )
{
	if ( argc != 2 )
		return 1;

	// std::cout << "START" << std::endl;
	GLFWwindow*	window;
	try {
		window = setupLibs();
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		return -1;
	}
	// std::string	vsPath = "srcs/shaders/" + std::string(argv[2]) + ".vs";
	// std::string	fsPath = "srcs/shaders/" + std::string(argv[2]) + ".fs";
	
	// int	currentShader = 0;
	shaders.push_back( new Shader( "srcs/shaders/basicLight.vs", "srcs/shaders/basicLight.fs" ) );
	shaders.push_back( new Shader( "srcs/shaders/normal.vs", "srcs/shaders/normal.fs" ) );
	shaders.push_back( new Shader( "srcs/shaders/mat.vs", "srcs/shaders/mat.fs" ) );
	shaders.push_back( new Shader( "srcs/shaders/vertCol.vs", "srcs/shaders/vertCol.fs" ) );

	// On Resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keypressed_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  
	glfwSetScrollCallback(window, scroll_callback);

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    // stbi_set_flip_vertically_on_load(true);

	glEnable(GL_DEPTH_TEST);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Load Model
	Model *	model =  new Model(argv[1], shaders[0]);

	// Render Loop
	while (!glfwWindowShouldClose(window)) {
		model->setShader( shaders[currentShaderId % shaders.size() ] );
		render( window, model );
	}
	
	// Terminate
	glfwTerminate();

	// shaders.clear();
	delete(shaders[0]);
	delete(shaders[1]);
	delete(shaders[2]);
	delete(shaders[3]);
	delete(model);

	return 0;
}
