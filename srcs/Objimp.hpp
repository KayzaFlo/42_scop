#ifndef OBJIMP_HPP__
# define OBJIMP_HPP__

#include <iostream>
#include <cmath>
#include <vector>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Mesh.hpp"
#include "Mtlimp.hpp"
#include "betterLog.h"

// struct Material {
// 	std::string				name;
// 	std::vector<Texture*>	textures;
// };

// struct s_Face
// {
// 	std::vector<uint>	iPosition;
// 	std::vector<uint>	iNormal;
// 	std::vector<uint>	iTexCoord;
// 	int					s;
// };

// struct s_Object
// {
// 	std::string				name;
// 	std::vector<s_Face>		faces;
// 	// std::string				matName;
// 	Material				mat;
// };



class Objimp
{
public:
	std::vector<Vec3>	vertices;
	std::vector<Vec3>	normals;
	std::vector<Vec2>	texCoords;
	std::vector<s_Object>	objects;
	std::vector<Mesh*>		meshes;
	std::vector<Material>	materials;
	
	Objimp( std::string path ) {
		directory = path.substr( 0, path.find_last_of( "/", path.size() ) + 1 );

		loadModel( path );

		for( size_t i = 0; i < objects.size(); i++ ) {
			meshes.push_back( createMesh(objects[i]) );
		}
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
		bool		smoothShading = -1;

		std::string line;
		while (std::getline(buffer, line, '\n')) {
			std::stringstream	line_buf;
			line_buf << line;
			std::string token;
			std::getline(line_buf, token, ' ');
			if ( token[0] == '#' || token[0] <= 32 || token[0] == 127 )
				continue;
			else if ( token == "mtllib" ) {
				// parse .mtl & create Material
				std::getline(line_buf, token, ' ');
				while (is_empty(token.c_str()))
					std::getline(line_buf, token, ' ');
				Mtlimp	mtlimp( std::string( directory + token ) );
				materials = mtlimp.materials;
				continue;
			}
			else if ( token == "g" ) {
				std::cerr << C_YEL << "\'" << token << "\' is not implemented yet and has been ignored" << C_RST << std::endl;
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
			else if ( token == "v" ) { // doesnt handle v v/vn/vt
				float	val[3];

				for (size_t i = 0; i < 3; i++)
				{
					std::getline(line_buf, token, ' ');
					while (is_empty(token.c_str()))
						std::getline(line_buf, token, ' ');
					val[i] = atof(token.c_str());
				}
				vertices.push_back(Vec3(val[0], val[1], val[2]));
			}
			else if ( token == "vn" ) {
				Vec3 vertex;
				std::getline(line_buf, token, ' ');
				vertex.x = atof(token.c_str());
				std::getline(line_buf, token, ' ');
				vertex.y = atof(token.c_str());
				std::getline(line_buf, token, ' ');
				vertex.z = atof(token.c_str());
				normals.push_back(vertex);
			}
			else if ( token == "vt" ) {
				Vec2 vertex;
				std::getline(line_buf, token, ' ');
				vertex.x = atof(token.c_str());
				std::getline(line_buf, token, ' ');
				vertex.y = atof(token.c_str());
				texCoords.push_back(vertex);
			}
			else if ( token == "usemtl" ) {
				std::getline(line_buf, token, ' ');
				while (is_empty(token.c_str()))
					std::getline(line_buf, token, ' ');
				for (size_t i = 0; i < materials.size(); i++) {
					if ( token == materials[i].name )
						currentObject.mat = materials[i];
				}
				continue;
			}
			else if ( token == "s" ) {
				std::getline(line_buf, token, ' ');
				if ( token == "off" )
					smoothShading = -1;
				else
					smoothShading = atoi(token.c_str());
				continue;
			}
			else if ( token == "f" ) { // doesnt handle negative/relative values
				s_Face	face;
				face.s = smoothShading;
				while ( std::getline(line_buf, token, ' ') ) {
					if (is_empty(token.c_str()))
						continue;
					std::stringstream	token_buf;
					token_buf << token;
					std::string sub_token;
					if ( !std::getline(token_buf, sub_token, '/') ) {
						// face.iPosition.push_back(std::stoi(sub_token.c_str()) - 1);
						continue;
					}
					face.iPosition.push_back(std::stoi(sub_token) - 1);
					if ( !std::getline(token_buf, sub_token, '/') )
						continue;
					face.iTexCoord.push_back(std::stoi(sub_token) - 1);
					if ( !std::getline(token_buf, sub_token, '/') )
						continue;
					face.iNormal.push_back(std::stoi(sub_token) - 1);
				}
				currentObject.faces.push_back(face);
			}
			else {
				std::cerr << C_RED << "\'" << token[0] << "\' is not a valid .obj parameter" << C_RST << std::endl;
				// exit(1);
			}
		}
		objects.push_back(currentObject);
	}

	void print() {
		// std::cout << "o " << name << std::endl;
		for (size_t i = 0; i < vertices.size(); i++) {
			if ( abs(vertices[i].x) > 20 )
				std::cerr << C_RED << "Weird value vert.pos.x: " << vertices[i].x << C_RST << std::endl;
			if ( abs(vertices[i].y) > 20 )
				std::cerr << C_RED << "Weird value vert.pos.y: " << vertices[i].y << C_RST << std::endl;
			if ( abs(vertices[i].z) > 20 )
				std::cerr << C_RED << "Weird value vert.pos.z: " << vertices[i].z << C_RST << " & x is " << vertices[i].x << std::endl;
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
		uint					indiceCount = 0;
		srand((unsigned)time(NULL));

		std::vector<s_Face>		f = obj.faces;
		for (size_t i = 0; i < f.size(); i++) {
			for (size_t n = 0; n < f[i].iPosition.size() - 2; n++) {
				if (
					f[i].iPosition[0] < 0 ||
					f[i].iPosition[0] > vertices.size() ||
					f[i].iPosition[1+n] < 0 ||
					f[i].iPosition[1+n] > vertices.size() ||
					f[i].iPosition[2+n] < 0 ||
					f[i].iPosition[2+n] > vertices.size()
				) {
					std::cerr << "Face Index wrong" << std::endl;
					exit(1);
				}

				Vec3 p1 = vertices[f[i].iPosition[0]];
				Vec3 p2 = vertices[f[i].iPosition[1 + n]];
				Vec3 p3 = vertices[f[i].iPosition[2 + n]];

				Vec3 n1 = f[i].iNormal.size() > 0 && normals.size() > f[i].iNormal[0] ? normals[f[i].iNormal[0]] : crossProduct( p1, p2, p3 );
				Vec3 n2 = f[i].iNormal.size() > 0 && normals.size() > f[i].iNormal[1+n] ? normals[f[i].iNormal[1+n]] : crossProduct( p2, p3, p1 );
				Vec3 n3 = f[i].iNormal.size() > 0 && normals.size() > f[i].iNormal[2+n] ? normals[f[i].iNormal[2+n]] : crossProduct( p3, p1, p2 );

				Vec2 t1 = f[i].iTexCoord.size() > 0 && texCoords.size() > f[i].iTexCoord[0] ? texCoords[f[i].iTexCoord[0]] : (Vec2){ p1.x + p1.z, p1.y };
				Vec2 t2 = f[i].iTexCoord.size() > 0 && texCoords.size() > f[i].iTexCoord[1+n] ? texCoords[f[i].iTexCoord[1 + n]] : (Vec2){ p2.x + p2.z, p2.y };
				Vec2 t3 = f[i].iTexCoord.size() > 0 && texCoords.size() > f[i].iTexCoord[2+n] ? texCoords[f[i].iTexCoord[2 + n]] : (Vec2){ p3.x + p3.z, p3.y };

				float r = rand() % 255 / 255.0f;
				float g = rand() % 255 / 255.0f;
				float b = rand() % 255 / 255.0f;
				Vec3 col = { r, g, b };

				o_vert.insert( o_vert.end(), { 
					{ p1, n1, t1, col },
					{ p2, n2, t2, col },
					{ p3, n3, t3, col }
				} );
				indiceCount += 3;
			}
		}
		
		for (size_t i = 0; i < indiceCount; i++) {
			o_ind.push_back(i);
		}
		
		return new Mesh( obj.name, o_vert, o_ind, obj.mat );
	}

	Vec3	crossProduct( Vec3 o, Vec3 a, Vec3 b ) {
		Vec3 lhs = { a.x - o.x, a.y - o.y, a.z - o.z };
		Vec3 rhs = { b.x - o.x, b.y - o.y, b.z - o.z };

		Vec3 ret = {
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
		};
		float mag = 1 / sqrt( ret.x*ret.x + ret.y*ret.y + ret.z*ret.z );
		return Vec3{ ret.x * mag, ret.y * mag, ret.z * mag };
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
