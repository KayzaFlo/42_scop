#include "Vec2.hpp"
using namespace scopm;

const	Vec2 Vec2::zero = { 0, 0 };
const	Vec2 Vec2::one = { 1, 1 };

// Constructors

Vec2::Vec2() : x(0), y(0) {}
Vec2::Vec2( float _x, float _y ) : x(_x), y(_y) {}
Vec2::Vec2( Vec2 const & src ) { *this = src; }
Vec2::~Vec2() {}

// Operators

Vec2 &	Vec2::operator=( Vec2 const & rhs ) {
	x = rhs.x;
	y = rhs.y;
	return *this;
}

Vec2		Vec2::operator+( Vec2 const & rhs ) const {
	return Vec2( x + rhs.x, y + rhs.y );
}

Vec2		Vec2::operator-( Vec2 const & rhs ) const {
	return Vec2( x - rhs.x, y - rhs.y );
}

Vec2		Vec2::operator*( float const & rhs ) const {
	return Vec2( x * rhs, y * rhs );
}
float		Vec2::operator[]( int i ) const { return array[i]; }
float		Vec2::operator[]( int i ) { return array[i]; }

// Methods


std::ostream &	operator<<( std::ostream & o, Vec2 const & rhs ) {
	o << "Vec2( " << rhs.x << ", " << rhs.y << " )" << std::endl;
	return o;
}
