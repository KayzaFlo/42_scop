#ifndef VECTOR3_HPP__
# define VECTOR3_HPP__

#include <iostream>
#include <cmath>

namespace scopm
{
	union Vector3 {
		struct {
			float	x;
			float	y;
			float	z;
		};
		float	array[3];

		Vector3();
		Vector3( float _x, float _y, float _z );
		Vector3( Vector3 const & src );
		~Vector3();

		Vector3 &	operator=( Vector3 const & rhs );
		Vector3		operator+( Vector3 const & rhs ) const;
		Vector3		operator-( Vector3 const & rhs ) const;
		Vector3		operator*( float const & rhs ) const;
		// Vector3		operator*( Matrix4x4 const & rhs ) const { return ?; } // Applly transformation Matrix
		float		operator[]( int i ) const; // useful ?


		Vector3	normalized() const;
		float	magnitude() const;

		static float	Dot( Vector3 lhs, Vector3 rhs );
		static float	Distance( Vector3 lhs, Vector3 rhs );
		static Vector3	Cross( Vector3 lhs, Vector3 rhs );

		static const	Vector3 zero;
		static const	Vector3 one;

	};

} // namespace scopm

std::ostream &	operator<<( std::ostream & o, scopm::Vector3 const & rhs );

#endif
