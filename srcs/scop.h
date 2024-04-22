#ifndef SCOP_H__
#define SCOP_H__

#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080

#include <iostream>
#include <cmath>
#include <vector>

#include "Camera.hpp"
extern Camera	camera;

struct Texture {
	uint32_t	id;
	std::string	type;
	std::string	path;
};

struct Vertex {
	Vec3	position;
	Vec3	normal;
	Vec2	texCoords;
	Vec3	color;
};

extern Vec2	horizontalAxis;
extern Vec2	verticalAxis;
extern Vec2	zAxis;

extern int	currentShaderId;

struct s_Face
{
	std::vector<uint>	iPosition;
	std::vector<uint>	iNormal;
	std::vector<uint>	iTexCoord;
	int					s;
};

struct Material {
	std::string				name;			// newmtl
	Vec3				ambient;		// Ka
	Vec3				diffuse;		// Kd
	Vec3				emissive;		// Ke
	Vec3				specular;		// Ks
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


void		framebuffer_size_callback(GLFWwindow* window, int width, int height);
void		keypressed_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void		mouse_callback(GLFWwindow* window, double xpos, double ypos);
void		scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

#endif
