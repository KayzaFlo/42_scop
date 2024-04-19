#ifndef SCOP_H__
#define SCOP_H__

#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080

#include <iostream>
#include <cmath>
#include <vector>


struct s_Vector2 {
	float x;
	float y;
};

// struct Vector3 {
// 	float x;
// 	float y;
// 	float z;
// };

#include "Camera.hpp"
extern Camera	camera;

struct Texture {
	uint32_t	id;
	std::string	type;
	std::string	path;
};

struct Vertex {
	Vector3	position;
	Vector3	normal;
	s_Vector2	texCoords;
};

extern s_Vector2	horizontalAxis;
extern s_Vector2	verticalAxis;
extern s_Vector2	zAxis;

struct s_Face
{
	std::vector<uint>	iPosition;
	std::vector<uint>	iNormal;
	std::vector<uint>	iTexCoord;
	int					s;
};

struct Material {
	std::string				name;			// newmtl
	Vector3				ambient;		// Ka
	Vector3				diffuse;		// Kd
	Vector3				emissive;		// Ke
	Vector3				specular;		// Ks
	float					specularExp;	// Ns
	float					dissolved;		// d
	// float					transparency;	// Tr (inverted: Tr = 1 - d) // d or Tr depend of implementation
	// Vector3				transmissionFilterColor;	// Tf
	float					opticalDensity;	// Ni
	uint					illum;			// i ( different illumination models, id from 0 to 10, illum 2 seems basics ) 
	std::vector<Texture>	textureMaps;	// map_Ka, map_Kd, map_Ks, map_Ns, map_d, map_bump/bump, disp, decal
};

struct s_Object
{
	std::string				name;
	std::vector<s_Face>		faces;
	// std::string				matName;
	Material				mat;
};

#endif
