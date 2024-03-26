#include "Shader.hpp"

Shader::Shader( const char* vertexPath, const char* fragmentPath ) {
	// 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try  {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();		
    }
    catch(std::ifstream::failure e) {
        std::cout << C_BRED << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << M_SEP << C_RST << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

	uint32_t	vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "VERTEX");

	uint32_t	fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void	Shader::use() {
	glUseProgram(ID);
}

void	Shader::setUniform( const std::string &name, bool value ) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void	Shader::setUniform( const std::string &name, int value ) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void	Shader::setUniform( const std::string &name, float value ) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void	Shader::setUniform( const std::string &name, float x, float y ) const {
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
void	Shader::setUniform( const std::string &name, float x, float y, float z ) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
void	Shader::setUniform( const std::string &name, float x, float y, float z, float w ) const {
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
void	Shader::setUniform( const std::string &name, Matrix4x4 mat ) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, mat.getRaw());
}

void	Shader::checkCompileErrors(unsigned int shader, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << C_BRED << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << M_SEP << C_RST << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << C_BRED << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << M_SEP << C_RST << std::endl;
		}
	}
}
