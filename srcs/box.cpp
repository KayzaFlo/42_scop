#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scopm.hpp>
#include <stb_image.h>

#include <iostream>

#include "Shader.hpp"
#include "Mesh.hpp"


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


Mesh	box() {
	uint32_t	tex;
	setupTex(&tex);

	std::vector<Vertex>		vertices = { // tbd by Parsing
		// positions		   // colors now normal	// texCoords
		{{ 0.5f,  0.5f,  0.5f},	{1.0f, 0.0f, 0.0},	{1.0f, 1.0f}},	// top right
		{{ 0.5f, -0.5f,  0.5f},	{0.0f, 1.0f, 0.0},	{1.0f, 0.0f}},	// bottom right
		{{-0.5f, -0.5f,  0.5f},	{1.0f, 0.0f, 0.0},	{0.0f, 0.0f}},	// bottom left
		{{-0.5f,  0.5f,  0.5f},	{0.0f, 1.0f, 0.0},	{0.0f, 1.0f}},	// top left 

		{{ 0.5f,  0.5f, -0.5f},	{1.0f, 0.0f, 0.0},	{1.0f, 1.0f}},
		{{ 0.5f, -0.5f, -0.5f},	{0.0f, 1.0f, 0.0},	{1.0f, 0.0f}},
		{{-0.5f, -0.5f, -0.5f},	{1.0f, 0.0f, 0.0},	{0.0f, 0.0f}},
		{{-0.5f,  0.5f, -0.5f},	{0.0f, 1.0f, 0.0},	{0.0f, 1.0f}}
	};
	std::vector<uint32_t>	indices = {
		0, 1, 3,
		1, 2, 3,
		0, 3, 4,
		3, 4, 7,
		4, 5, 7,
		5, 6, 7,
		3, 6, 7,
		2, 3, 6,
		0, 4, 5,
		0, 1, 5,
		1, 2, 5,
		2, 5, 6
	};
	std::vector<Texture>	textures = {
		{ .id = 0, .type = "texture_diffuse" }
	};

	return Mesh(vertices, indices, textures);
}