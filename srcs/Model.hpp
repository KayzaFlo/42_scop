#ifndef MODEL_HPP__
# define MODEL_HPP__

#include <iostream>
#include <cmath>
#include <vector>
#include <scopm.hpp>
#include <sys/stat.h>
#include <stb_image.h>

#include "Shader.hpp"
#include "Mesh.hpp"

Mesh		box();


class Model
{
public:
	std::vector<Mesh>	meshes;
	Model( char *path ) {
		loadModel( path );
	}
	~Model() {}
	void	Draw( Shader &shader ) {
		for (uint i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader);
	}

private:
	// std::vector<Mesh>	meshes;
	std::string			directory;

	void	loadModel( std::string path ) {
		std::ofstream		file;
		std::stringstream	buffer;

	// struct stat s;
	// if ( stat(path.c_str(), &s) == 0 ) {
	// 	if ( s.st_mode & S_IFREG )
	// 		std::cerr << C_GRN << ".mtl file found" << C_RST << std::endl;
	// 	else
	// 		std::cerr << C_RED << ".mtl file error" << C_RST << std::endl;
	// }
	// else
	// 	std::cerr << C_RED << ".mtl file not found" << C_RST << std::endl;

		file.open(path.c_str(), std::ifstream::in);
		if (file.is_open() == false)
			std::cerr << C_RED << "open .mtl file error" << C_RST << std::endl;
		buffer << file.rdbuf();


		uint32_t	tex;
		setupTex(&tex);


		std::vector<Vertex>		vertices;
		std::vector<uint>		indices;
		std::vector<Texture>	textures = {
			{ .id = tex, .type = "texture_diffuse" }
		};

		std::string line;
		while (std::getline(buffer, line, '\n')) {
			std::string token;
			// std::cerr << "getline: " << line << std::endl;
			char * tmp = strtok( (char*)line.c_str(), " " );
			if (!tmp)
				continue;
			token = tmp;
			if ( token == "#" || token == "" )
				continue;
			else if ( token == "mtllib" ) {
				std::cerr << C_YEL << "\'" << line << "\' is not implemented yet and has been ignored" << C_RST << std::endl;
				continue;
			}
			else if ( token == "o" ) {
				std::cerr << C_YEL << "\'" << line << "\' is not implemented yet and has been ignored" << C_RST << std::endl;
				continue;
			}
			else if ( token == "v" ) {
				Vertex vertex;
				token = strtok( NULL, " " );
				vertex.position.x = atof(token.c_str());
				token = strtok( NULL, " " );
				vertex.position.y = atof(token.c_str());
				token = strtok( NULL, " " );
				vertex.position.z = atof(token.c_str());
				// vertex.normal = {0, 0, 0};
				// vertex.texCoords = {0, 0};
				vertices.push_back(vertex);
			}
			else if ( token == "usemtl" ) {
				std::cerr << C_YEL << "\'" << line << "\' is not implemented yet and has been ignored" << C_RST << std::endl;
				continue;
			}
			else if ( token == "s" ) {
				std::cerr << C_YEL << "\'" << line << "\' is not implemented yet and has been ignored" << C_RST << std::endl;
				continue;
			}
			else if ( token == "f" ) {
				token = strtok( NULL, " " );
				indices.push_back(atof(token.c_str()));
				token = strtok( NULL, " " );
				indices.push_back(atof(token.c_str()));
				token = strtok( NULL, " " );
				indices.push_back(atof(token.c_str()));
			}
			else {
				std::cerr << C_RED << "\'" << line << "\' is not ad valid .mtl line" << C_RST << std::endl;
				continue;
			}
		}

		Mesh * a = new Mesh(vertices, indices, textures);
		meshes.push_back(*a);

		// Mesh box = box();
		// meshes.push_back(&box);

		std::cout << meshes[0].indices[4] << std::endl;
	}

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
};


#endif
