#ifndef OBJIMP_HPP__
# define OBJIMP_HPP__

#include <iostream>
#include <cmath>
#include <vector>
// #include <scopm.hpp>
#include <sys/stat.h>
// #include <stb_image.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// #include "Shader.hpp"
#include "Mesh.hpp"
#include "betterLog.h"


// struct s_Vector3 {
// 	float x;
// 	float y;
// };

// struct s_Vector3 {
// 	float x;
// 	float y;
// 	float z;
// };

// struct Texture {
// 	uint32_t	id;
// 	std::string	type;
// 	std::string	path;
// };

struct Material {
	std::string				name;
	std::vector<Texture*>	textures;
};

struct s_Face
{
	std::vector<uint>	iPosition;
	std::vector<uint>	iNormal;
	std::vector<uint>	iTexCoord;
	bool				s;
};

struct s_Object
{
	std::string				name;
	std::vector<s_Face>		faces;
	std::string				matName;
	std::vector<Material*>	materials;
};



class Objimp
{
public:
	std::vector<s_Vector3>	vertices;
	std::vector<s_Vector3>	normals;
	std::vector<s_Vector2>	texCoords;
	std::vector<s_Object>	objects;
	std::vector<Mesh*>		meshes;
	
	Objimp( char const *path ) {
		loadModel( path );
		// print();
		for( size_t i = 0; i < objects.size(); i++ ) {
		// for( size_t i = 0; i < 4; i++ ) {
			meshes.push_back( createMesh(objects[i]) );
		}
		// 	std::cerr << "got it" << std::endl;
	}
	~Objimp() {}

private:
	std::string			directory;

	void	loadModel( std::string path ) {
		std::ofstream		file;
		std::stringstream	buffer;

		file.open(path.c_str(), std::ifstream::in);
		if (file.is_open() == false)
			std::cerr << C_RED << "open .obj file error" << C_RST << std::endl;
		buffer << file.rdbuf();

		s_Object	currentObject;
		int 		vCount = 0;
		int 		nCount = 0;
		int 		tCount = 0;
		int 		vMax = 0;
		int 		nMax = 0;
		int 		tMax = 0;
		bool		smoothShading = false;

		std::string line;
		while (std::getline(buffer, line, '\n')) {
			std::stringstream	line_buf;
			line_buf << line;
			std::string token;
			std::getline(line_buf, token, ' ');
			// if (!tmp)
				// continue;
			// token = tmp;
			if ( token == "#" || token[0] == 13 || token[0] == 0 )
				continue;
			else if ( token == "mtllib" ) {
				// parse .mtl & create Material
				continue;
			}
			else if ( token == "o" ) {
				if ( currentObject.name != "" ) {
					objects.push_back(currentObject);
					currentObject.faces.clear();
				}
				std::getline(line_buf, token, ' ');
				currentObject.name = token;
				continue;
			}
			else if ( token == "v" ) {
				s_Vector3 vertex;
				std::getline(line_buf, token, ' ');
				vertex.x = atof(token.c_str());
				std::getline(line_buf, token, ' ');
				vertex.y = atof(token.c_str());
				std::getline(line_buf, token, ' ');
				vertex.z = atof(token.c_str());
				vertices.push_back(vertex);
				vCount++;
			}
			else if ( token == "vn" ) {
				s_Vector3 vertex;
				std::getline(line_buf, token, ' ');
				vertex.x = atof(token.c_str());
				std::getline(line_buf, token, ' ');
				vertex.y = atof(token.c_str());
				std::getline(line_buf, token, ' ');
				vertex.z = atof(token.c_str());
				normals.push_back(vertex);
				nCount++;
			}
			else if ( token == "vt" ) {
				s_Vector2 vertex;
				std::getline(line_buf, token, ' ');
				vertex.x = atof(token.c_str());
				std::getline(line_buf, token, ' ');
				vertex.y = atof(token.c_str());
				texCoords.push_back(vertex);
				tCount++;
			}
			else if ( token == "usemtl" ) {
				std::getline(line_buf, token, ' ');
				currentObject.matName = token;
				// std::cerr << C_YEL << "\'" << line.c_str() << "\' is not implemented yet and has been ignored" << C_RST << std::endl;
				continue;
			}
			else if ( token == "s" ) {
				std::getline(line_buf, token, ' ');
				if ( token == "1" )
					smoothShading = true;
				else if ( token == "off" )
					smoothShading = false;
				else
					std::cerr << C_YEL << "\'" << line.c_str() << "\' bad parameter" << C_RST << std::endl;
				continue;
			}
			else if ( token == "f" ) {
				s_Face	face;
				face.s = smoothShading;
				while ( std::getline(line_buf, token, ' ') ) {
					std::stringstream	token_buf;
					token_buf << token;
					std::string sub_token;
					if ( !std::getline(token_buf, sub_token, '/') )
						break;
			if ( std::stoi(sub_token.c_str()) - 1 > vMax ) vMax = std::stoi(sub_token.c_str()) - 1;
					face.iPosition.push_back(std::stoi(sub_token.c_str()) - 1);
					if ( !std::getline(token_buf, sub_token, '/') )
						break;
			if ( std::stoi(sub_token.c_str()) - 1 > tMax ) tMax = std::stoi(sub_token.c_str()) - 1;
					face.iTexCoord.push_back(std::stoi(sub_token.c_str()) - 1);
					if ( !std::getline(token_buf, sub_token, '/') )
						break;
			if ( std::stoi(sub_token.c_str()) - 1 > nMax ) nMax = std::stoi(sub_token.c_str()) - 1;
					face.iNormal.push_back(std::stoi(sub_token.c_str()) - 1);
				}
				currentObject.faces.push_back(face);
			}
			else {
				std::cerr << C_RED << "\'" << line.c_str() << "\' is not a valid .mtl line" << C_RST << std::endl;
				exit(1);
			}
		}
		objects.push_back(currentObject);

			std::cerr << "vCount: " << vCount << std::endl;
			std::cerr << "nCount: " << nCount << std::endl;
			std::cerr << "tCount: " << tCount << std::endl;
			std::cerr << "vMax: " << vMax << std::endl;
			std::cerr << "nMax: " << nMax << std::endl;
			std::cerr << "tMax: " << tMax << std::endl;
	}

	void print() {
		// std::cout << "o " << name << std::endl;
		for (size_t i = 0; i < vertices.size(); i++) {
			if ( abs(vertices[i].x) > 20 )
				std::cerr << C_RED << "Weird value vert.pos.x: " << vertices[i].x << C_RST << std::endl;
			if ( abs(vertices[i].y) > 20 )
				std::cerr << C_RED << "Weird value vert.pos.y: " << vertices[i].y << C_RST << std::endl;
			if ( abs(vertices[i].z) > 20 )
				std::cerr << C_RED << "Weird value vert.pos.z: " << vertices[i].z << C_RST << std::endl;
			std::cout << "v " << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << std::endl;
		}
		std::cout << std::endl;
		for (size_t i = 0; i < normals.size(); i++) {
			std::cout << "vn " << normals[i].x << " " << normals[i].y << " " << normals[i].z << std::endl;
			if ( abs(normals[i].x) > 1 )
				std::cerr << C_RED << "Weird value norm.x: " << normals[i].x << C_RST << std::endl;
			if ( abs(normals[i].y) > 1 )
				std::cerr << C_RED << "Weird value norm.y: " << normals[i].y << C_RST << std::endl;
			if ( abs(normals[i].z) > 1 )
				std::cerr << C_RED << "Weird value norm.z: " << normals[i].z << C_RST << std::endl;
		}
		std::cout << std::endl;
		for (size_t i = 0; i < texCoords.size(); i++) {
			std::cout << "vt " << texCoords[i].x << " " << texCoords[i].y << std::endl;
			if ( abs(texCoords[i].x) > 1 )
				std::cerr << C_RED << "Weird value texCoord.x: " << texCoords[i].x << C_RST << std::endl;
			if ( abs(texCoords[i].y) > 1 )
				std::cerr << C_RED << "Weird value texCoord.y: " << texCoords[i].y << C_RST << std::endl;
		}
		std::cout << std::endl;
		for (size_t i = 0; i < objects.size(); i++) {
			std::cout << "o: " << objects[i].name << std::endl;
			for (size_t j = 0; j < objects[i].faces.size(); j++) {
				std::cout << "f ";
				for (size_t k = 0; k < objects[i].faces[j].iPosition.size(); k++) {
					std::cout << objects[i].faces[j].iPosition[k] << " ";
				}
				std::cout << std::endl;
				std::cout << "fn ";
				for (size_t k = 0; k < objects[i].faces[j].iNormal.size(); k++) {
					std::cout << objects[i].faces[j].iNormal[k] << " ";
				}
				std::cout << std::endl;
				std::cout << "ft ";
				for (size_t k = 0; k < objects[i].faces[j].iTexCoord.size(); k++) {
					std::cout << objects[i].faces[j].iTexCoord[k] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	}

	Mesh *	createMesh( s_Object & obj ) {
		std::vector<Vertex>		o_vert;
		std::vector<uint32_t>	o_ind;
		std::vector<Texture>	o_tex;
		uint					indiceCount = 0;

		std::vector<s_Face>		f = obj.faces;
			// std::cerr << "fsize: " << f.size() << std::endl;
		for (size_t i = 0; i < f.size(); i++) {
			// std::cerr << "i(" << i << ") ";
			for (size_t n = 0; n < f[i].iPosition.size() - 2; n++) {
				// (0, 1+n, 2+n)
				uint i1 = f[i].iPosition[0];
				uint i2 = f[i].iPosition[1 + n];
				uint i3 = f[i].iPosition[2 + n];
				uint in1 = f[i].iNormal[0];
				uint in2 = f[i].iNormal[1 + n];
				uint in3 = f[i].iNormal[2 + n];
				uint it1 = f[i].iTexCoord[0];
				uint it2 = f[i].iTexCoord[1 + n];
				uint it3 = f[i].iTexCoord[2 + n];
				Vertex v1 = { vertices[i1], normals[in1], texCoords[it1] };
				o_vert.push_back( v1 );
				Vertex v2 = { vertices[i2], normals[in2], texCoords[it2] };
				o_vert.push_back( v2 );
				Vertex v3 = { vertices[i3], normals[in3], texCoords[it3] };
				o_vert.push_back( v3 );
				indiceCount += 3;
			}
		}
			// std::cerr << "loop end" << std::endl;
		Texture t = { 0, "a", "b" };
		o_tex.push_back( t );
		
			// std::cerr << "ret" << std::endl;

		for (size_t i = 0; i < indiceCount; i++) {
			o_ind.push_back(i);
		}
		

		return new Mesh( obj.name, o_vert, o_ind, o_tex );
	}
};


#endif
