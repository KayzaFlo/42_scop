// #define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

float vertices[] = { // tbd by Parsing
	 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0,	// top right
	 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0,	// bottom right
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0,	// bottom left
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0,	// top left 
	 0.0f,  1.0f, 0.0f,		0.0f, 0.0f, 1.0		// top top 
};
uint32_t indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3,    // second triangle
	0, 3, 4    // second triangle
};

void	setupVertices( uint32_t *VBO, uint32_t *VAO, uint32_t *EBO ) {

	glGenVertexArrays(1, VAO);	// Vertex Array Object
	glGenBuffers(1, VBO);	// Vertex Buffer Object
	glGenBuffers(1, EBO);	// Element Buffer Object
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// location = 0
		// vec3
		// float
		// normalized = false
		// space between consecutive vertex attributes so 6 float, x y z & r, g, b
		// offset
	// position attribute set to location = 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// position attribute set to location = 1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// unbinds
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// settings
	glPolygonMode(GL_FRONT, GL_FILL); // default
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
}
