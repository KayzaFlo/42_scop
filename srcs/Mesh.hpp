#ifndef MESH_HPP__
# define MESH_HPP__

#include <iostream>
#include <cmath>
#include <vector>
#include <scopm.hpp>

#include "Shader.hpp"
#include "scop.h"

class Mesh
{
public:
	std::string				name;					// o
	std::vector<Vertex>		vertices;				// v // vn // vt
	// ???											// s
	std::vector<uint32_t>	indices;				// f?
	std::vector<Texture>	textures;				// tex
	Material				mat;					// usemtl, mtllib
	uint	VAO;

	Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material & mat) {
		// std::cout << "Mesh's constructor called (" << name << ")" << std::endl;
		this->name = name;
		this->vertices = vertices;
		this->indices = indices;
		// this->mat = mat;
		this->textures = mat.textureMaps;

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
	}
	Mesh( Mesh const & src ) {
		(void)src;
		std::cerr << "mesh copy constructor\n";
	}
	~Mesh() {
		// std::cout << "Mesh's destructor called (" << this->name << ")" << std::endl;
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
	void	Draw(Shader *shader) {
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int bumpNbr = 1;
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
			else if(name == "texture_bump")
				number = std::to_string(bumpNbr++);

			// shader->setUniform( (name + number).c_str(), (int)i );
            glUniform1i(glGetUniformLocation(shader->ID, (name + number).c_str()), i);
			// (void)shader;
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		// draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		// reset to default, good practice
		glActiveTexture(GL_TEXTURE0);
	}

	void print() {
		std::cout << "o " << name << std::endl;
		for (size_t i = 0; i < vertices.size(); i++) {
			if ( abs(vertices[i].position.x) > 20 )
				std::cerr << C_RED << "Weird value vert.pos.x: " << vertices[i].position.x << C_RST << std::endl;
			if ( abs(vertices[i].position.y) > 20 )
				std::cerr << C_RED << "Weird value vert.pos.y: " << vertices[i].position.y << C_RST << std::endl;
			if ( abs(vertices[i].position.z) > 20 )
				std::cerr << C_RED << "Weird value vert.pos.z: " << vertices[i].position.z << C_RST << std::endl;
			std::cout << "v " << vertices[i].position.x << " " << vertices[i].position.y << " " << vertices[i].position.z << std::endl;
		}
		std::cout << std::endl;
		for (size_t i = 0; i < vertices.size(); i++) {
			std::cout << "vn " << vertices[i].normal.x << " " << vertices[i].normal.y << " " << vertices[i].normal.z << std::endl;
			if ( abs(vertices[i].normal.x) > 1 )
				std::cerr << C_RED << "Weird value vert.normal.x: " << vertices[i].normal.x << C_RST << std::endl;
			if ( abs(vertices[i].normal.y) > 1 )
				std::cerr << C_RED << "Weird value vert.normal.y: " << vertices[i].normal.y << C_RST << std::endl;
			if ( abs(vertices[i].normal.z) > 1 )
				std::cerr << C_RED << "Weird value vert.normal.z: " << vertices[i].normal.z << C_RST << std::endl;
		}
		std::cout << std::endl;
		for (size_t i = 0; i < vertices.size(); i++) {
			std::cout << "vt " << vertices[i].texCoords.x << " " << vertices[i].texCoords.y << std::endl;
			if ( abs(vertices[i].texCoords.x) > 1 )
				std::cerr << C_RED << "Weird value vert.texCoord.x: " << vertices[i].texCoords.x << C_RST << std::endl;
			if ( abs(vertices[i].texCoords.y) > 1 )
				std::cerr << C_RED << "Weird value vert.texCoord.y: " << vertices[i].texCoords.y << C_RST << std::endl;
		}
		std::cout << std::endl;
		for (size_t i = 0; i < indices.size(); i++) {
			if ( indices[i] > 100000 )
				std::cerr << C_RED << "Weird value indices: " << indices[i] << C_RST << std::endl;
			std::cout << "f " << indices[i];
			if ( i % 3 == 2 )
				std::cout << std::endl;
			else
				std::cout << " ";
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

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

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
