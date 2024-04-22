#include "Vec3.hpp"
using namespace scopm;

const	Vec3 Vec3::zero = Vec3( 0, 0, 0 );
const	Vec3 Vec3::one = Vec3( 1, 1, 1 );

// Constructors

Vec3::Vec3() : x(0), y(0), z(0) {}
Vec3::Vec3( float _x, float _y, float _z ) : x(_x), y(_y), z(_z) {}
Vec3::Vec3( Vec3 const & src ) { *this = src; }
Vec3::~Vec3() {}

// Operators

Vec3 &	Vec3::operator=( Vec3 const & rhs ) {
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

Vec3		Vec3::operator+( Vec3 const & rhs ) const {
	return Vec3( x + rhs.x, y + rhs.y, z + rhs.z );
}

Vec3		Vec3::operator-( Vec3 const & rhs ) const {
	return Vec3( x - rhs.x, y - rhs.y, z - rhs.z );
}

Vec3		Vec3::operator*( float const & rhs ) const {
	return Vec3( x * rhs, y * rhs, z * rhs );
}
float		Vec3::operator[]( int i ) const { return array[i]; }

// Methods

Vec3	Vec3::normalized() const {
	return *this * ( 1 / this->magnitude() );
}
float	Vec3::magnitude() const {
	return sqrt( x*x + y*y + z*z );
}

float	Vec3::Dot( Vec3 lhs, Vec3 rhs ) {
	return ( (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) );
}
float	Vec3::Distance( Vec3 lhs, Vec3 rhs ) {
	return sqrt( pow( rhs.x - lhs.x, 2 ) + pow( rhs.y - lhs.y, 2 ) + pow( rhs.z - lhs.z, 2 ) );
}
Vec3	Vec3::Cross( Vec3 lhs, Vec3 rhs ) {
	return Vec3(
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x
	);
}

std::ostream &	operator<<( std::ostream & o, Vec3 const & rhs ) {
	o << "Vector3( " << rhs.x << ", " << rhs.y << ", " << rhs.z << " )" << std::endl;
	return o;
}
