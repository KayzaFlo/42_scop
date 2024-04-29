#ifndef TEXTURE_HPP__
# define TEXTURE_HPP__

#include <iostream>
#include <unistd.h>
#include <fcntl.h>

#include <glad/glad.h>
#include "betterLog.h"

struct Texture {
	uint32_t		id;
	std::string		type;
	const char * 	path;
	int				w, h, bpp, opp, sl, size;
	u_char *		img;

	Texture( std::string _type, const char * _path ) :
		id(0),
		type(_type),
		path(_path),
		w(0),
		h(0),
		bpp(0),
		opp(0),
		sl(0),
		size(0),
		img(nullptr) {}

	int	read_header() {
		FILE	*file;

		if ( path == nullptr ) {
			std::cerr << C_YEL << "No bmp file found: using default tex" << C_RST << std::endl;
			return (1);
		}
		if ((file = fopen(path, "r")) == NULL) {
			std::cerr << C_BRED << "bmp file opening (fopen) failed." << C_RST << std::endl;
			return (1);
		}
		int	tmp;
		fseek(file, 0, SEEK_SET);
		fread(&tmp, 2, 1, file);
		if (tmp != 0x4D42) {
			std::cerr << C_BRED << "\'" << path << "\' is not a bmp file." << C_RST << std::endl;
			return (1);
		}
		fseek(file, 16, SEEK_CUR);
		fread(&w, 4, 1, file);
		fread(&h, 4, 1, file);
		fseek(file, 2, SEEK_CUR);
		fread(&bpp, 2, 1, file);
		fclose(file);
		opp = bpp / 8;
		sl = w * opp;
		w < 0 ? w = -w : 0;
		h < 0 ? h = -h : 0;
		size = sl * h * 2;
		return (0);
	}

	void	get_image(char *buffer, int i) {
		int	k;
		int	j;

		k = 0;
		img = (u_char*)calloc(size, sizeof(u_char));
		while (i >= 0)
		{
			i -= sl;
			j = 0;
			while (j < sl)
			{
				img[k + j] = (u_char)buffer[i + j + 2];
				img[k + j + 1] = (u_char)buffer[i + j + 1];
				img[k + j + 2] = (u_char)buffer[i + j];
				j += 3;
			}
			k += sl;
		}
	}

	int	load_bmp() {
		int		fd;
		int		i;
		char	*buffer;

		if ( read_header() )
			return (1);
		if ((fd = open(path, O_RDWR)) == -1) {
			std::cerr << C_BRED << "bmp file opening failed." << C_RST << std::endl;
			return (1);
		}
		buffer = (char*)calloc(size + 1, sizeof(char));
		lseek(fd, 54, SEEK_SET);
		i = read(fd, buffer, size);
		get_image(buffer, i);
		free(buffer);
		close(fd);
		return (0);
	}

	void	setupTex() {
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);	// when texture minified	// mipmap onloy useful for min
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);				// when texture magnified

		if ( load_bmp() == 1) {
			img = (u_char*)calloc(16, sizeof(GL_UNSIGNED_BYTE));
			memset(img, 255, sizeof(GL_UNSIGNED_BYTE) * 16);
			w = 4;
			h = 4;
		}
		if (img) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
			glGenerateMipmap(GL_TEXTURE_2D);
		} else
			std::cerr << C_BRED << "Failed to load texture \'" << path << "\'" << C_RST << std::endl;
		free(img);
	}
};


#endif