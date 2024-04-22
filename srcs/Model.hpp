#ifndef MODEL_HPP__
# define MODEL_HPP__

#include <iostream>
#include <cmath>
#include <vector>
#include <scopm.hpp>
#include <sys/stat.h>
#include <stb_image.h>

#include "Shader.hpp"
#include "Mesh.hpp"
#include "Objimp.hpp"


class Model
{
public:
	Mat4	transform = Mat4::identity;
	Vec3	position = Vec3::zero;
	Vec3	rotation = Vec3::zero;

	Model( char *path, Shader *s ) : shader(s) {
		Objimp *OBJ_file = new Objimp( path );
		for (uint i = 0; i < OBJ_file->meshes.size(); i++)
			meshes.push_back(OBJ_file->meshes[i]);
		delete(OBJ_file);
	}
	Model( Model const & src ) {
		(void)src;
		std::cerr << "Model copy constructor\n";
	}
	~Model() {
		for (uint i = 0; i < meshes.size(); i++)
			delete(meshes[i]);
	}
	void	Draw() {
		// transform = Matrix4x4::identity;
		// Vector3 tmp = Vector3( position.x, position.y, position.z );
		// transform = Matrix4x4::Translate(transform, tmp );
		shader->setUniform("model", transform);
		shader->use();

		for (uint i = 0; i < meshes.size(); i++) {
			meshes[i]->Draw(shader);
		}
	}

	Shader *	getShader() { return shader; }
	void		setShader( Shader * s ) { shader = s; }

private:
	std::vector<Mesh*>	meshes;
	Shader *			shader;

};


#endif
