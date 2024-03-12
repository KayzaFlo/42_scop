// #define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "betterLog.h"

#include <iostream>

float vertices[] = { // tbd by Parsing
	// positions			// colors			// texCoords
	 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0,	1.0f, 1.0f,	// top right
	 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0,	1.0f, 0.0f,	// bottom right
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0,	0.0f, 0.0f,	// bottom left
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0,	0.0f, 1.0f,	// top left 
	 0.0f,  1.0f, 0.0f,		0.0f, 0.0f, 1.0,	0.5f, 1.5f	// top top 
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute set to location = 1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texCoord attribute set to location = 2
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// unbinds
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// settings
	glPolygonMode(GL_FRONT, GL_FILL); // default
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
}

#include <stb_image.h>

void	setupTex( uint32_t *texture ) {
	// uint32_t	texture;
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);

	// tx wraping / filtering options (on the currently bound texture object)
	// float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); // defaut is GL_REPEAT
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);	// when texture minified	// mipmap onloy useful for min
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);				// when texture magnified

	int	width, height, nrChannels;
	u_char	*data = stbi_load("resources/wall.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cerr << C_BRED << "Failed to load texture" << C_RST << std::endl;
	stbi_image_free(data);
}
