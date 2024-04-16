#ifndef MTLIMP_HPP__
# define MTLIMP_HPP__

#include <iostream>
#include <cmath>
#include <vector>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <stb_image.h>

#include "Mesh.hpp"
#include "betterLog.h"

// struct Material {
// 	std::string				name;			// newmtl
// 	s_Vector3				ambient;		// Ka
// 	s_Vector3				diffuse;		// Kd
// 	s_Vector3				emissive;		// Ke
// 	s_Vector3				specular;		// Ks
// 	float					specularExp;	// Ns
// 	float					dissolved;		// d
// 	// float					transparency;	// Tr (inverted: Tr = 1 - d) // d or Tr depend of implementation
// 	// s_Vector3				transmissionFilterColor;	// Tf
// 	float					opticalDensity;	// Ni
// 	uint					illum;			// i ( different illumination models, id from 0 to 10, illum 2 seems basics ) 
// 	std::vector<Texture>	textureMaps;	// map_Ka, map_Kd, map_Ks, map_Ns, map_d, map_bump/bump, disp, decal
// };

class Mtlimp
{
public:
	std::string				directory;
	std::vector<Material>	materials;
	
	Mtlimp(  std::string path ) {
		directory = path.substr( 0, path.find_last_of( "/", path.size() ) + 1 );
		loadMaterials( path );
	}
	~Mtlimp() {}

private:

	void	loadMaterials( std::string path ) {
		std::ofstream		file;
		std::stringstream	buffer;

		file.open(path.c_str(), std::ifstream::in);
		if (file.is_open() == false)
			std::cerr << C_RED << "open .obj file error" << C_RST << std::endl;
		buffer << file.rdbuf();

		Material	currentMat;

		std::string line;
		while (std::getline(buffer, line, '\n')) {
			std::stringstream	line_buf;
			line_buf << line;
			std::string token;
			std::getline(line_buf, token, ' ');
			if ( token[0] == '#' || token[0] <= 32 || token[0] == 127 )
				continue;
			else if ( token == "newmtl" ) {
				if ( currentMat.name != "" ) {
					materials.push_back(currentMat);
					currentMat.textureMaps.clear(); //
				}
				std::getline(line_buf, token, ' ');
				currentMat.name = token;
				continue;
			}
			else if ( token == "Ka" ) {
				float	val[3];
				for (size_t i = 0; i < 3; i++)
				{
					std::getline(line_buf, token, ' ');
					while (is_empty(token.c_str()))
						std::getline(line_buf, token, ' ');
					val[i] = atof(token.c_str());
				}
				currentMat.ambient = s_Vector3{ val[0], val[1], val[2] };
			}
			else if ( token == "Kd" ) {
				float	val[3];
				for (size_t i = 0; i < 3; i++)
				{
					std::getline(line_buf, token, ' ');
					while (is_empty(token.c_str()))
						std::getline(line_buf, token, ' ');
					val[i] = atof(token.c_str());
				}
				currentMat.diffuse = s_Vector3{ val[0], val[1], val[2] };
			}
			else if ( token == "Ke" ) {
				float	val[3];
				for (size_t i = 0; i < 3; i++)
				{
					std::getline(line_buf, token, ' ');
					while (is_empty(token.c_str()))
						std::getline(line_buf, token, ' ');
					val[i] = atof(token.c_str());
				}
				currentMat.emissive = s_Vector3{ val[0], val[1], val[2] };
			}
			else if ( token == "Ks" ) {
				float	val[3];
				for (size_t i = 0; i < 3; i++)
				{
					std::getline(line_buf, token, ' ');
					while (is_empty(token.c_str()))
						std::getline(line_buf, token, ' ');
					val[i] = atof(token.c_str());
				}
				currentMat.specular = s_Vector3{ val[0], val[1], val[2] };
			}
			else if ( token == "Ns" ) {
				std::getline(line_buf, token, ' ');
				while (is_empty(token.c_str()))
					std::getline(line_buf, token, ' ');
				currentMat.specularExp = atof(token.c_str());
			}
			else if ( token == "Ni" ) {
				std::getline(line_buf, token, ' ');
				while (is_empty(token.c_str()))
					std::getline(line_buf, token, ' ');
				currentMat.opticalDensity = atof(token.c_str());
			}
			else if ( token == "d" ) {
				std::getline(line_buf, token, ' ');
				while (is_empty(token.c_str()))
					std::getline(line_buf, token, ' ');
				currentMat.dissolved = atof(token.c_str());
			}
			else if ( token == "illum" ) {
				std::getline(line_buf, token, ' ');
				while (is_empty(token.c_str()))
					std::getline(line_buf, token, ' ');
				currentMat.illum = (int)atof(token.c_str());
			}
			else if ( token == "map_Kd" ) {
				std::getline(line_buf, token, ' ');
				while (is_empty(token.c_str()))
					std::getline(line_buf, token, ' ');
				std::string	fileName = token;
				uint	texId;
				setupTex( &texId, directory + token);
				currentMat.textureMaps.push_back(Texture{ texId, "texture_diffuse", directory + token });
			}
			else if ( token == "map_Ks" ) {
				std::getline(line_buf, token, ' ');
				while (is_empty(token.c_str()))
					std::getline(line_buf, token, ' ');
				std::string	fileName = token;
				uint	texId;
				setupTex( &texId, directory + token);
				currentMat.textureMaps.push_back(Texture{ texId, "texture_specular", directory + token });
			}
			else if ( token == "map_Bump" ) {
				std::getline(line_buf, token, ' ');
				while (is_empty(token.c_str()))
					std::getline(line_buf, token, ' ');
				std::string	fileName = token;
				uint	texId;
				setupTex( &texId, directory + token);
				currentMat.textureMaps.push_back(Texture{ texId, "texture_bump", directory + token });
			}
			else {
				std::cerr << C_RED << "\'" << token << "\' is not a valid .obj parameter" << C_RST << std::endl;
				// exit(1);
			}
		}
		materials.push_back(currentMat);
	}

	void print() {
	}

	int is_empty(const char *s) {
		while (*s != '\0') {
			if (!isspace((unsigned char)*s))
			return 0;
			s++;
		}
		return 1;
	}

	void	setupTex( uint32_t *texture, std::string path ) {
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
		u_char	*data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		} else
			std::cerr << C_BRED << "Failed to load texture \'" << path << "\'" << C_RST << std::endl;
		stbi_image_free(data);
		// glBindTexture(GL_TEXTURE_2D, 0);
	}

};


#endif
