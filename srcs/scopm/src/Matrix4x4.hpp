#ifndef MATRIX4X4_HPP__
# define MATRIX4X4_HPP__

#include <iostream>
#include <cmath>
#include "Vector3.hpp"

const float	rawIdentity[] = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

namespace scopm
{
	class Matrix4x4 {
	private:
		float	*raw;


		void copyArray( const float	arr[] ) {
			std::memcpy( raw, arr, sizeof(float) * 16 );
		}

	public:
		Matrix4x4() {
			raw = (float*) std::calloc( 16, sizeof(float) );
		}
		Matrix4x4( float * _raw ) {
			raw = (float*) std::calloc( 16, sizeof(float) );
			copyArray( _raw );
		}
		Matrix4x4( Matrix4x4 const & src ) { *this = src; }
		~Matrix4x4() {}

		Matrix4x4 &	operator=( Matrix4x4 const & rhs ) {
			std::memcpy( raw, rhs.raw, sizeof(float) * 16 );
			return *this;
		}
		Matrix4x4		operator+( Matrix4x4 const & rhs ) const {
			Matrix4x4 ret( raw );
			for (int i = 0; i < 16; i++) {
				ret.raw[i] = ret.raw[i] + rhs.raw[i];
			}			
			return ret;
		}
		Matrix4x4		operator-( Matrix4x4 const & rhs ) const {
			Matrix4x4 ret( raw );
			for (int i = 0; i < 16; i++) {
				ret.raw[i] = ret.raw[i] - rhs.raw[i];
			}			
			return ret;
		}
		Matrix4x4		operator*( float const & rhs ) const {
			Matrix4x4 ret( raw );
			for (int i = 0; i < 16; i++) {
				ret.raw[i] = ret.raw[i] * rhs;
			}			
			return ret;
		}
		Matrix4x4		operator*( Matrix4x4 const & rhs ) const {
			float *ret;
			ret = (float*) std::calloc( 16, sizeof(float) );
			for (int i = 0; i < 16; i++) {
				for (int c = 0; c < 4; c++) {
					int a = std::floor( i / 4 ) * 4 + c;
					int b = i % 4 + c * 4;
					ret[i] += raw[a] * rhs.raw[b];
				}
			}
			return Matrix4x4( ret );
		}

		float	getElem( int i, int j ) const {
			return *( raw + i * 4 + j );
		}

		// static Matrix4x4	Translate( Matrix4x4 transformationMatrix, Vector3 translation );
		// static Matrix4x4	Rotate( Matrix4x4 transformationMatrix, float angleInRad, Vector3 normalizedVecAxis );
		// static Matrix4x4	Scale( Matrix4x4 transformationMatrix, Vector3 scale );

		static const	Matrix4x4 zero;
		static const	Matrix4x4 identity;

	};

	#endif

	std::ostream &	operator<<( std::ostream & o, Matrix4x4 const & rhs ) {
		for (int i = 0; i < 4; i++) {
			o << "[ ";
			for (int j = 0; j < 4; j++) {
				o << rhs.getElem( i, j ) << " ";
			}
			o << "]" << std::endl;
		}
		o << std::endl;
		return o;
	}
	
	const Matrix4x4	Matrix4x4::zero = Matrix4x4();
	const Matrix4x4	Matrix4x4::identity = Matrix4x4( (float *)rawIdentity );

	// Matrix4x4::Matrix4x4( float newMat[] ) : mat{newMat} {}


} // namespace scopm


