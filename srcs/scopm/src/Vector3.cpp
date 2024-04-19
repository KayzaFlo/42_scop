#include "Vector3.hpp"
using namespace scopm;

const	Vector3 Vector3::zero = Vector3( 0, 0, 0 );
const	Vector3 Vector3::one = Vector3( 1, 1, 1 );

// Constructors

Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3( float _x, float _y, float _z ) : x(_x), y(_y), z(_z) {}
Vector3::Vector3( Vector3 const & src ) { *this = src; }
Vector3::~Vector3() {}

// Operators

Vector3 &	Vector3::operator=( Vector3 const & rhs ) {
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

Vector3		Vector3::operator+( Vector3 const & rhs ) const {
	return Vector3( x + rhs.x, y + rhs.y, z + rhs.z );
}

Vector3		Vector3::operator-( Vector3 const & rhs ) const {
	return Vector3( x - rhs.x, y - rhs.y, z - rhs.z );
}

Vector3		Vector3::operator*( float const & rhs ) const {
	return Vector3( x * rhs, y * rhs, z * rhs );
}
float		Vector3::operator[]( int i ) const { return array[i]; }

// Methods

Vector3	Vector3::normalized() const {
	return *this * ( 1 / this->magnitude() );
}
float	Vector3::magnitude() const {
	return sqrt( x*x + y*y + z*z );
}

float	Vector3::Dot( Vector3 lhs, Vector3 rhs ) {
	return ( (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) );
}
float	Vector3::Distance( Vector3 lhs, Vector3 rhs ) {
	return sqrt( pow( rhs.x - lhs.x, 2 ) + pow( rhs.y - lhs.y, 2 ) + pow( rhs.z - lhs.z, 2 ) );
}
Vector3	Vector3::Cross( Vector3 lhs, Vector3 rhs ) {
	return Vector3(
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x
	);
}

std::ostream &	operator<<( std::ostream & o, Vector3 const & rhs ) {
	o << "Vector3( " << rhs.x << ", " << rhs.y << ", " << rhs.z << " )" << std::endl;
	return o;
}
