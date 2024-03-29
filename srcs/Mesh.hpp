#ifndef MESH_HPP__
# define MESH_HPP__

#include <iostream>
#include <cmath>
#include <vector>
#include <scopm.hpp>

#include "Shader.hpp"

struct s_Vector2 {
	float x;
	float y;
};

struct s_Vector3 {
	float x;
	float y;
	float z;
};

struct Texture {
	uint32_t	id;
	std::string	type;
};

struct Vertex {
	s_Vector3	position;
	s_Vector3	normal;
	s_Vector2	texCoords;
};

class Mesh
{
public:
	std::string				name;					// o
	std::vector<Vertex>		vertices;				// v // vn // vt
	// ???											// s
	std::vector<uint32_t>	indices;				// f?
	std::vector<Texture>	textures;				// tex
	// Material				_mat;					// usemtl, mtllib
	uint	VAO;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
		std::cout << "Mesh's constructor called" << std::endl;
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
	}
	~Mesh() {
		std::cout << "Mesh's destructor called" << std::endl;
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
	void	Draw(Shader &shader) {
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		for(unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = textures[i].type;
			if(name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if(name == "texture_specular")
				number = std::to_string(specularNr++);

			shader.setUniform(("material." + name + number).c_str(), (int)i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		// draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		// reset to default, good practice
		glActiveTexture(GL_TEXTURE0);
		// std::cerr << "draw" << std::endl;
	}

	void print() {
		for(size_t i = 0; i < vertices.size(); i++) {
			std::cerr << C_GRY << vertices[i].position.x << ", " << vertices[i].position.y << ", " << vertices[i].position.z << std::endl;
			std::cerr << C_GRY << vertices[i].normal.x << ", " << vertices[i].normal.y << ", " << vertices[i].normal.z << std::endl;
			std::cerr << C_GRY << vertices[i].texCoords.x << ", " << vertices[i].texCoords.y << std::endl;
			std::cerr << C_RST << "---" << std::endl;
		}
		for(size_t i = 0; i < indices.size(); i++) {
			std::cerr << C_GRY << indices[i] << std::endl;
			std::cerr << C_RST << "---" << std::endl;
		}
	}

private:
	uint	VBO, EBO;

	void setupMesh() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);  

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

// Struct is sequencial in memory so it's easy to just pass the values to the glVertexAttribPointer but vector might be a problem
		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);	
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);	
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

		glBindVertexArray(0);
	}
};

#endif