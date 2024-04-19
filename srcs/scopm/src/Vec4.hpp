#ifndef VEC4_HPP__
# define VEC4_HPP__

#include <iostream>
#include <cmath>

namespace scopm
{
	union Vec4 {
		struct {
			float	x;
			float	y;
			float	z;
			float	w;
		};
		float	array[4];

		Vec4();
		Vec4( float _x, float _y, float _z, float _w );
		Vec4( Vec4 const & src );
		~Vec4();

		Vec4 &	operator=( Vec4 const & rhs );
		Vec4		operator+( Vec4 const & rhs ) const;
		Vec4		operator-( Vec4 const & rhs ) const;
		Vec4		operator*( float const & rhs ) const;
		float		operator[]( int i ) const;
		float		operator[]( int i );

		static const	Vec4 zero;
		static const	Vec4 one;

	};

} // namespace scopm

std::ostream &	operator<<( std::ostream & o, scopm::Vec4 const & rhs );

#endif
