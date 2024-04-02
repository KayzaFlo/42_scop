#ifndef MODEL_HPP__
# define MODEL_HPP__

#include <iostream>
#include <cmath>
#include <deque>
#include <scopm.hpp>
#include <sys/stat.h>
#include <stb_image.h>

#include "Shader.hpp"
#include "Mesh.hpp"

Mesh		box();


class Model
{
public:
	std::deque<Mesh>	meshes;
	Model( char *path ) {
		loadModel( path );
	}
	~Model() {}
	void	Draw( Shader &shader ) {
		// std::cout << meshes.size() << std::endl;
		for (uint i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader);
		// meshes[70].Draw(shader);
	}

private:
	// std::deque<Mesh>	meshes;
	std::string			directory;

	void	loadModel( std::string path ) {
		std::ofstream		file;
		std::stringstream	buffer;

	// struct stat s;
	// if ( stat(path.c_str(), &s) == 0 ) {
	// 	if ( s.st_mode & S_IFREG )
	// 		std::cerr << C_GRN << ".obj file found" << C_RST << std::endl;
	// 	else
	// 		std::cerr << C_RED << ".obj file error" << C_RST << std::endl;
	// }
	// else
	// 	std::cerr << C_RED << ".obj file not found" << C_RST << std::endl;

		file.open(path.c_str(), std::ifstream::in);
		if (file.is_open() == false)
			std::cerr << C_RED << "open .obj file error" << C_RST << std::endl;
		buffer << file.rdbuf();


		uint32_t	tex;
		setupTex(&tex);


		// std::deque<Vertex>		vertices;
		std::deque<s_Vector3>	vertices;
		std::deque<s_Vector3>	normals;
		std::deque<s_Vector2>	texCoords;
		std::deque<uint>		indices;
		std::deque<Texture>	textures = {
			{ .id = tex, .type = "texture_diffuse" }
		};
		std::string				name = "";

		int vCount = 0;
		int nCount = 0;
		int tCount = 0;

		std::string line;
		while (std::getline(buffer, line, '\n')) {
			std::string token;
			// std::cerr << "getline: " << line << std::endl;
			char * tmp = strtok( (char*)line.c_str(), " " );
			if (!tmp)
				continue;
			token = tmp;
			if ( token == "#" || token[0] == 13 )
				continue;
			else if ( token == "mtllib" ) {
				// std::cerr << C_YEL << "\'" << line.c_str() << "\' is not implemented yet and has been ignored" << C_RST << std::endl;
				continue;
			}
			else if ( token == "o" ) {
				// std::cerr << C_YEL << "\'" << line.c_str() << "\' is not implemented yet and has been ignored" << C_RST << std::endl;
				// if ( name == "Plane.014__0" )
				// 	break;
				// if ( name != "" ) {
				// 	pushMesh(name, vertices, normals, texCoords, indices, textures);
				// 	vertices.clear();
				// 	normals.clear();
				// 	texCoords.clear();
				// 	indices.clear();
				// }
				token = strtok( NULL, " " );
				name = token;
				continue;
			}
			else if ( token == "v" ) {
				s_Vector3 vertex;
				token = strtok( NULL, " " );
				vertex.x = atof(token.c_str());
				token = strtok( NULL, " " );
				vertex.y = atof(token.c_str());
				token = strtok( NULL, " " );
				vertex.z = atof(token.c_str());
				vertices.push_back(vertex);
				vCount++;
			}
			else if ( token == "vn" ) {
				s_Vector3 vertex;
				token = strtok( NULL, " " );
				vertex.x = atof(token.c_str());
				token = strtok( NULL, " " );
				vertex.y = atof(token.c_str());
				token = strtok( NULL, " " );
				vertex.z = atof(token.c_str());
				normals.push_back(vertex);
				nCount++;
			}
			else if ( token == "vt" ) {
				s_Vector2 vertex;
				token = strtok( NULL, " " );
				vertex.x = atof(token.c_str());
				token = strtok( NULL, " " );
				vertex.y = atof(token.c_str());
				texCoords.push_back(vertex);
				tCount++;

				if ( vertex.x > 1 || vertex.x < 0 )
					std::cerr << C_RED << "weird x: " << vertex.x << C_RED << std::endl;
				if ( vertex.y > 1 || vertex.y < 0 )
					std::cerr << C_RED << "weird y: " << vertex.x << C_RED << std::endl;
			}
			else if ( token == "usemtl" ) {
				// std::cerr << C_YEL << "\'" << line.c_str() << "\' is not implemented yet and has been ignored" << C_RST << std::endl;
				continue;
			}
			else if ( token == "s" ) {
				// std::cerr << C_YEL << "\'" << line.c_str() << "\' is not implemented yet and has been ignored" << C_RST << std::endl;
				continue;
			}
			else if ( token == "f" ) {
				token = strtok( NULL, " " );
				indices.push_back(atof(token.c_str()) - 1);
				token = strtok( NULL, " " );
				indices.push_back(atof(token.c_str()) - 1);
				token = strtok( NULL, " " );
				indices.push_back(atof(token.c_str()) - 1);
			}
			else {
				std::cerr << C_RED << "\'" << line.c_str() << "\' is not ad valid .mtl line" << C_RST << std::endl;
				continue;
			}
		}

		pushMesh(name, vertices, normals, texCoords, indices, textures);

	}

	void pushMesh(
		std::string				name,
		std::deque<s_Vector3>	vertices,
		std::deque<s_Vector3>	normals,
		std::deque<s_Vector2>	texCoords,
		std::deque<uint>		indices,
		std::deque<Texture>		textures
		)
	{
		std::deque<Vertex>		ver;

		for (size_t i = 0; i < vertices.size(); i++) {
			(void)normals;
			s_Vector3 v;
			s_Vector3 n;
			s_Vector2 t;
			v = {vertices[i].x, vertices[i].y, vertices[i].z};
			if ( i >= normals.size() )
				n = {0,0,0};
			else
				n = {normals[i].x, normals[i].y, normals[i].z};
			if ( i >= texCoords.size() )
				t = {0,0};
			else
				t = {texCoords[i].x, texCoords[i].y};
			ver.push_back({ v, n, t });
		}
		// std::cout << std::endl;
		// std::cout << "v: " << vCount << " n: " << nCount << " t: " << tCount << std::endl;
		

		Mesh * a = new Mesh(name, ver, indices, textures);
		meshes.push_back(*a);
	}

	void	setupTex( uint32_t *texture ) {
		// uint32_t	texture;
		glGenTextures(1, texture);
		glBindTexture(GL_TEXTURE_2D, *texture);

		// tx wraping / filtering options (on the currently bound texture object)
		// float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); // defaut is GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);	// when texture minified	// mipmap onloy useful for min
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);				// when texture magnified

		int	width, height, nrChannels;
		u_char	*data = stbi_load("resources/diffuse.jpg", &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		} else
			std::cerr << C_BRED << "Failed to load texture" << C_RST << std::endl;
		stbi_image_free(data);
	}
};


#endif
