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

#include "Texture.hpp"
#include "Mesh.hpp"
#include "betterLog.h"

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
			std::cerr << C_RED << "open .mtl file error" << C_RST << std::endl;
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
					if ( currentMat.textureMaps.size() == 0 ) {
						Texture	tex = Texture( "texture_specular", nullptr );
						tex.setupTex();
						currentMat.textureMaps.push_back(tex);
					}
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
				currentMat.ambient = Vec3(val[0], val[1], val[2]);
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
				currentMat.diffuse = Vec3(val[0], val[1], val[2]);
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
				currentMat.emissive = Vec3(val[0], val[1], val[2]);
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
				currentMat.specular = Vec3(val[0], val[1], val[2]);
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
				std::string		path = directory + token;
				Texture	tex = Texture( "texture_diffuse", path.c_str() );
				tex.setupTex();
				currentMat.textureMaps.push_back(tex);
			}
			else if ( token == "map_Ks" ) {
				std::getline(line_buf, token, ' ');
				while (is_empty(token.c_str()))
					std::getline(line_buf, token, ' ');
				std::string		path = directory + token;
				Texture	tex = Texture( "texture_specular", path.c_str() );
				tex.setupTex();
				currentMat.textureMaps.push_back(tex);
			}
			else if ( token == "map_Bump" ) {
				std::getline(line_buf, token, ' ');
				while (is_empty(token.c_str()))
					std::getline(line_buf, token, ' ');
				std::string		path = directory + token;
				Texture	tex = Texture( "texture_bump", path.c_str() );
				tex.setupTex();
				currentMat.textureMaps.push_back(tex);
			}
			else {
				std::cerr << C_YEL << "\'" << token << "\' is not a valid .obj parameter and has been ignored" << C_RST << std::endl;
			}
		}
		if ( currentMat.textureMaps.size() == 0 ) {
				Texture	tex = Texture( "texture_diffuse", nullptr );
				tex.setupTex();
				currentMat.textureMaps.push_back(tex);
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
};


#endif
