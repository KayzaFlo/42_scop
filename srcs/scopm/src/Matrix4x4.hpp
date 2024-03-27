#ifndef MATRIX4X4_HPP__
# define MATRIX4X4_HPP__

#include <iostream>
#include <cmath>
#include "Vector3.hpp"

namespace scopm
{
	class Matrix4x4 {
	private:
		float	*_raw;
		// Warning
		// our data is :		while glm is:	so needed to transpose when passing as uniform
		// 0, 1, 2, 3,			0, 4, 8, c,
		// 4, 5, 6, 7,			1, 5, 9, d,
		// 8, 9, a, b,			2, 6, a, e,
		// c, d, e, f			3, 7, b, f

	public:
		Matrix4x4();
		Matrix4x4( float * __raw );
		Matrix4x4( Matrix4x4 const & src );
		~Matrix4x4();

		Matrix4x4 &	operator=( Matrix4x4 const & rhs );
		Matrix4x4		operator+( Matrix4x4 const & rhs ) const;
		Matrix4x4		operator-( Matrix4x4 const & rhs ) const;
		Matrix4x4		operator*( float const & rhs ) const;
		Matrix4x4		operator*( Matrix4x4 const & rhs ) const;
		float			operator[]( int i ) const;


		float *	getRaw() const;

		static Matrix4x4	Translate( Matrix4x4 transformationMatrix, Vector3 translation );
		static Matrix4x4	Rotate( Matrix4x4 transformationMatrix, float angleInRad, Vector3 normalizedVecAxis );
		static Matrix4x4	Scale( Matrix4x4 transformationMatrix, Vector3 scale );
		static Matrix4x4	Perspective( float fovy, float aspect, float zNear, float zFar );

		static const	Matrix4x4 zero;
		static const	Matrix4x4 identity;

	};

} // namespace scopm

std::ostream &	operator<<( std::ostream & o, scopm::Matrix4x4 const & rhs );

#endif
