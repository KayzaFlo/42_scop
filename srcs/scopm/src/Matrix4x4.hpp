#ifndef MATRIX4X4_HPP__
# define MATRIX4X4_HPP__

#include <iostream>
#include <cmath>
#include "Vector3.hpp"
#include "Vec4.hpp"

namespace scopm
{
	union Matrix4x4 {
		Vec4	vectors[4];
		float	array[16];
		float	d_arr[4][4];
		// Warning
		// our data is :		while glm is:	so needed to transpose when passing as uniform
		// 0, 1, 2, 3,			0, 4, 8, c,
		// 4, 5, 6, 7,			1, 5, 9, d,
		// 8, 9, a, b,			2, 6, a, e,
		// c, d, e, f			3, 7, b, f

		Matrix4x4();
		Matrix4x4( float a );
		Matrix4x4( float arr[16] );
		Matrix4x4( Matrix4x4 const & src );
		~Matrix4x4();

		Matrix4x4 &		operator=( Matrix4x4 const & rhs );
		Matrix4x4		operator+( Matrix4x4 const & rhs ) const;
		Matrix4x4		operator-( Matrix4x4 const & rhs ) const;
		Matrix4x4		operator*( float const & rhs ) const;
		Matrix4x4		operator*( Matrix4x4 const & rhs ) const;
		Vec4			operator[]( int i ) const;
		Vec4			operator[]( int i );


		// float *	getRaw() const;

		static Matrix4x4	Translate( Matrix4x4 transformationMatrix, Vector3 translation );
		static Matrix4x4	Rotate( Matrix4x4 transformationMatrix, float angleInRad, Vector3 normalizedVecAxis );
		static Matrix4x4	Scale( Matrix4x4 transformationMatrix, Vector3 scale );
		static Matrix4x4	Perspective( float fovy, float aspect, float zNear, float zFar );
		static Matrix4x4	LookAt( Vector3 eye, Vector3 center, Vector3 up );

		static const	Matrix4x4 zero;
		static const	Matrix4x4 identity;

	};

} // namespace scopm

std::ostream &	operator<<( std::ostream & o, scopm::Matrix4x4 const & rhs );

#endif
