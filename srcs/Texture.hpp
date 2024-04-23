#ifndef TEXTURE_HPP__
# define TEXTURE_HPP__

#include <iostream>

#include <stb_image.h>
#include <glad/glad.h>
#include "betterLog.h"

struct Texture {
	uint32_t		id;
	std::string		type;
	const char * 	path;

	void	setupTex() {
		// uint32_t	texture;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		// tx wraping / filtering options (on the currently bound texture object)
		// float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); // defaut is GL_REPEAT
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);	// when texture minified	// mipmap onloy useful for min
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);				// when texture magnified

		int	width, height, nrChannels;
		u_char	*data = nullptr;
		if ( path == nullptr ) {
			data = (u_char*)calloc(16, sizeof(GL_UNSIGNED_BYTE));
			memset(data, 255, sizeof(GL_UNSIGNED_BYTE) * 16);
			width = 4;
			height = 4;
		} else
			data = stbi_load(path, &width, &height, &nrChannels, 0);
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