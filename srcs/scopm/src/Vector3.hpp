#ifndef VECTOR3_HPP__
# define VECTOR3_HPP__

#include <iostream>
#include <cmath>

namespace scopm
{
	class Vector3 {
	private:
		

	public:
		Vector3() : x(0), y(0), z(0) {}
		Vector3( float x, float y, float z ) : x(x), y(y), z(z) {}
		Vector3( Vector3 const & src ) { *this = src; }
		~Vector3() {}

		Vector3 &	operator=( Vector3 const & rhs ) {
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			return *this;
		}
		Vector3		operator+( Vector3 const & rhs ) const { return Vector3( x + rhs.x, y + rhs.y, z + rhs.z ); }
		Vector3		operator-( Vector3 const & rhs ) const { return Vector3( x - rhs.x, y - rhs.y, z - rhs.z ); }
		Vector3		operator*( float const & rhs ) const { return Vector3( x * rhs, y * rhs, z * rhs ); }
		// Vector3		operator*( Matrix4x4 const & rhs ) const { return ?; } // Applly transformation Matrix
		Vector3		operator/( float const & rhs ) const { return Vector3( x / rhs, y / rhs, z / rhs ); }
		// float		operator[]( int i ) const { // useful ?
		// 	switch (i) {
		// 		case 0: return x;
		// 		case 1: return y;
		// 		case 2: return z;
		// 		default: return 0;
		// 	}
		// }

		float x;
		float y;
		float z;

		Vector3	normalized() const {
			float	len = this->magnitude();
			return Vector3( x / len, y / len, z / len );
		}
		float	magnitude() const {
			return sqrt( x*x + y*y + z*z );
		}

		static float	Dot( Vector3 lhs, Vector3 rhs ) {
			return ( (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) );
		}
		static float	Distance( Vector3 lhs, Vector3 rhs ) {
			return sqrt( pow( rhs.x - lhs.x, 2 ) + pow( rhs.z - lhs.y, 2 ) + pow( rhs.z - lhs.z, 2 ) );
		}
		static Vector3	Cross( Vector3 lhs, Vector3 rhs ){
			return Vector3(
				lhs.y * rhs.z - lhs.z * rhs.y,
				lhs.z * rhs.x - lhs.x * rhs.z,
				lhs.x * rhs.y - lhs.y * rhs.x
			);
		}
	};

	std::ostream &	operator<<( std::ostream & o, scopm::Vector3 const & rhs ) {
		o << "Vector3( " << rhs.x << ", " << rhs.y << ", " << rhs.z << " )" << std::endl;
		return o;
	}
	
} // namespace scopm

	#endif

