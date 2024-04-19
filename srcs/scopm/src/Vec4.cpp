#include "Vec4.hpp"
using namespace scopm;

const	Vec4 Vec4::zero = { 0, 0, 0, 0 };
const	Vec4 Vec4::one = { 1, 1, 1, 1 };

// Constructors

Vec4::Vec4() : x(0), y(0), z(0) {}
Vec4::Vec4( float _x, float _y, float _z, float _w ) : x(_x), y(_y), z(_z), w(_w) {}
Vec4::Vec4( Vec4 const & src ) { *this = src; }
Vec4::~Vec4() {}

// Operators

Vec4 &	Vec4::operator=( Vec4 const & rhs ) {
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

Vec4		Vec4::operator+( Vec4 const & rhs ) const {
	return Vec4( x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w );
}

Vec4		Vec4::operator-( Vec4 const & rhs ) const {
	return Vec4( x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w );
}

Vec4		Vec4::operator*( float const & rhs ) const {
	return Vec4( x * rhs, y * rhs, z * rhs, w * rhs );
}
float		Vec4::operator[]( int i ) const { return array[i]; }
float		Vec4::operator[]( int i ) { return array[i]; }

// Methods


std::ostream &	operator<<( std::ostream & o, Vec4 const & rhs ) {
	o << "Vec4( " << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << " )" << std::endl;
	return o;
}
