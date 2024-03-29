#ifndef SHADER_HPP__
# define SHADER_HPP__

#include <glad/glad.h>
#include <scopm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "betterLog.h"

class Shader
{
public:
	uint32_t	ID;

	Shader( const char* vertexPath, const char* fragmentPath );
	~Shader();

	void use();

	void	setUniform( const std::string &name, bool value ) const;
	void	setUniform( const std::string &name, int value ) const;
	void	setUniform( const std::string &name, float value ) const;
	void	setUniform( const std::string &name, float x, float y ) const;
	void	setUniform( const std::string &name, float x, float y, float z ) const;
	void	setUniform( const std::string &name, float x, float y, float z, float w ) const;
	void	setUniform( const std::string &name, Matrix4x4 mat ) const;

	void	checkCompileErrors(unsigned int shader, std::string type);
};


#endif