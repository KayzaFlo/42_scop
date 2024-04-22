#ifndef VEC3_HPP__
# define VEC3_HPP__

#include <iostream>
#include <cmath>

namespace scopm
{
	union Vec3 {
		struct {
			float	x;
			float	y;
			float	z;
		};
		float	array[3];

		Vec3();
		Vec3( float _x, float _y, float _z );
		Vec3( Vec3 const & src );
		~Vec3();

		Vec3 &	operator=( Vec3 const & rhs );
		Vec3		operator+( Vec3 const & rhs ) const;
		Vec3		operator-( Vec3 const & rhs ) const;
		Vec3		operator*( float const & rhs ) const;
		// Vector3		operator*( Matrix4x4 const & rhs ) const { return ?; } // Applly transformation Matrix
		float		operator[]( int i ) const; // useful ?


		Vec3	normalized() const;
		float	magnitude() const;

		static float	Dot( Vec3 lhs, Vec3 rhs );
		static float	Distance( Vec3 lhs, Vec3 rhs );
		static Vec3	Cross( Vec3 lhs, Vec3 rhs );

		static const	Vec3 zero;
		static const	Vec3 one;

	};

} // namespace scopm

std::ostream &	operator<<( std::ostream & o, scopm::Vec3 const & rhs );

#endif
