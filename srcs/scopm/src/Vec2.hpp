#ifndef VEC2_HPP__
# define VEC2_HPP__

#include <iostream>
#include <cmath>

namespace scopm
{
	union Vec2 {
		struct {
			float	x;
			float	y;
		};
		float	array[2];

		Vec2();
		Vec2( float _x, float _y );
		Vec2( Vec2 const & src );
		~Vec2();

		Vec2 &		operator=( Vec2 const & rhs );
		Vec2		operator+( Vec2 const & rhs ) const;
		Vec2		operator-( Vec2 const & rhs ) const;
		Vec2		operator*( float const & rhs ) const;
		float		operator[]( int i ) const;
		float		operator[]( int i );

		static const	Vec2 zero;
		static const	Vec2 one;

	};

} // namespace scopm

std::ostream &	operator<<( std::ostream & o, scopm::Vec2 const & rhs );

#endif
