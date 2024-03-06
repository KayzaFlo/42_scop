#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// current state : https://learnopengl.com/Getting-started/Hello-Triangle

GLFWwindow*	init() {
	std::cout << "START" << std::endl;
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

void	framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	(void)window;
	glViewport(0, 0, width, height);
	std::cout << "w: " << width << " - h: " << height << std::endl;
}

void	processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	// Quit with Escape key
		glfwSetWindowShouldClose(window, true);
}

void	render(GLFWwindow *window, uint32_t shaderProgram, uint32_t VAO) {
	(void)window;
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}

uint32_t	createVertexShader() {
	const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
	uint32_t	vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//Errors
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		throw std::runtime_error("\e[31mERROR::SHADER::VERTEX::COMPILATION_FAILED\n" + std::string(infoLog) + "\e[0m");
	} else {
		std::cout << "\e[32mVertexShader Compilation SUCCESS\e[0m" << std::endl;
	}
	return vertexShader;
}

uint32_t	createFragmentShader() {
	const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";
	uint32_t	fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//Errors
	int  success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		throw std::runtime_error("\e[31mERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" + std::string(infoLog) + "\e[0m");
	}
	std::cout << "\e[32mFragmentShader Compilation SUCCESS\e[0m" << std::endl;
	return fragmentShader;
}

uint32_t	createShaderProgram( uint32_t vertexShader, uint32_t fragmentShader ) {
	uint32_t	shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Errors
	int  success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		throw std::runtime_error("\e[31mERROR::SHADER::PROGRAM::CLINK_FAILED\n" + std::string(infoLog) + "\e[0m");
	} else {
		std::cout << "\e[32mShader Program Linked SUCCESS\e[0m" << std::endl;
	}
	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

int main()
{
	GLFWwindow*		window;
	uint32_t	shaderProgram;
	try {
		window = init();

		// Create SHADER ------------------------
		uint32_t	vertexShader = createVertexShader( /* Probably passing glsl file here */ );
		uint32_t	fragmentShader = createFragmentShader(/* Probably passing glsl file here */ );
		shaderProgram = createShaderProgram( vertexShader, fragmentShader );
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		return -1;
	}
	

	// On Resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// Create Obj TESTING
	float vertices[] = { // tbd by Parsing
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,  // top left 
		 0.0f,  1.0f, 0.0f   // top top 
	};
	uint32_t indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3,    // second triangle
		0, 3, 4    // second triangle
	};
	uint32_t	VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// location = 0
	// vec3
	// float
	// normalized = false
	// space between consecutive vertex attributes so 3 float, x y z
	// offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT, GL_FILL); // default
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe

	// Render Loop
	std::cout << "LOOP" << std::endl;
	while (!glfwWindowShouldClose(window)) 	{
		processInput(window);

		render(window, shaderProgram, VAO);

		glfwSwapBuffers(window);	// Render this iteration buffer
		glfwPollEvents();	// Check if any events are triggered andd call correspind functions / callbacks
	}
	
	// Terminate
	std::cout << "TERMINATE" << std::endl;
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}
