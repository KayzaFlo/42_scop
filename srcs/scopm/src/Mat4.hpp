#ifndef MAT4_HPP__
# define MAT4_HPP__

#include <iostream>
#include <cmath>
#include "Vec3.hpp"
#include "Vec4.hpp"

namespace scopm
{
	union Mat4 {
		Vec4	vectors[4];
		float	array[16];
		float	d_arr[4][4];
		// Warning
		// our data is :		while glm is:	so needed to transpose when passing as uniform
		// 0, 1, 2, 3,			0, 4, 8, c,
		// 4, 5, 6, 7,			1, 5, 9, d,
		// 8, 9, a, b,			2, 6, a, e,
		// c, d, e, f			3, 7, b, f

		Mat4();
		Mat4( float a );
		Mat4( float arr[16] );
		Mat4( Mat4 const & src );
		~Mat4();

		Mat4 &		operator=( Mat4 const & rhs );
		Mat4		operator+( Mat4 const & rhs ) const;
		Mat4		operator-( Mat4 const & rhs ) const;
		Mat4		operator*( float const & rhs ) const;
		Mat4		operator*( Mat4 const & rhs ) const;
		Vec4			operator[]( int i ) const;
		Vec4			operator[]( int i );


		// float *	getRaw() const;

		static Mat4	Translate( Mat4 transformationMatrix, Vec3 translation );
		static Mat4	Rotate( Mat4 transformationMatrix, float angleInRad, Vec3 normalizedVecAxis );
		static Mat4	Scale( Mat4 transformationMatrix, Vec3 scale );
		static Mat4	Perspective( float fovy, float aspect, float zNear, float zFar );
		static Mat4	LookAt( Vec3 eye, Vec3 center, Vec3 up );

		static const	Mat4 zero;
		static const	Mat4 identity;

	};

} // namespace scopm

std::ostream &	operator<<( std::ostream & o, scopm::Mat4 const & rhs );

#endif
