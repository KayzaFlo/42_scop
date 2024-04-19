#include "Matrix4x4.hpp"
using namespace scopm;


const Matrix4x4	Matrix4x4::zero = {};
const Matrix4x4	Matrix4x4::identity = Matrix4x4(1);

//////////////////////////
//-----CONSTRUCTORS-----//
//////////////////////////

Matrix4x4::Matrix4x4() : array() {}
Matrix4x4::Matrix4x4( float a ) : array() {
	for (int i = 0; i < 4; i++)
		d_arr[i][i] = a;
}
Matrix4x4::Matrix4x4( float a[16] ) : array() {
	for (int i = 0; i < 16; i++)
		array[i] = a[i];
}
Matrix4x4::Matrix4x4( Matrix4x4 const & src ) { *this = src; }
Matrix4x4::~Matrix4x4() {}


///////////////////////
//-----OPERATORS-----//
///////////////////////

Matrix4x4 &		Matrix4x4::operator=( Matrix4x4 const & rhs ) {
	for (int i = 0; i < 16; i++)
		array[i] = rhs.array[i];
	return *this;
}
Matrix4x4		Matrix4x4::operator+( Matrix4x4 const & rhs ) const {
	Matrix4x4 ret = {};
	for (int i = 0; i < 16; i++)
		ret.array[i] = array[i] + rhs.array[i];
	return ret;
}
Matrix4x4		Matrix4x4::operator-( Matrix4x4 const & rhs ) const {
	Matrix4x4 ret = {};
	for (int i = 0; i < 16; i++)
		ret.array[i] = array[i] - rhs.array[i];
	return ret;
}
Matrix4x4		Matrix4x4::operator*( float const & rhs ) const {
	Matrix4x4 ret = {};
	for (int i = 0; i < 16; i++)
		ret.array[i] = array[i] * rhs;
	return ret;
}
Matrix4x4		Matrix4x4::operator*( Matrix4x4 const & rhs ) const {
	Matrix4x4 ret = {};
	for (int i = 0; i < 16; i++) {
		for (int c = 0; c < 4; c++) {
			int a = std::floor( i / 4 ) * 4 + c;
			int b = i % 4 + c * 4;
			ret.array[i] += array[a] * rhs.array[b];
		}
	}
	return ret;
}
Vec4			Matrix4x4::operator[]( int i ) const { return vectors[i]; }
Vec4			Matrix4x4::operator[]( int i ) { return vectors[i]; }


/////////////////////
//-----GETTERS-----//
/////////////////////

// float *			Matrix4x4::getRaw() const {
// 	return &(array[0]);
// }


/////////////////////
//-----METHODS-----//
/////////////////////



/////////////////////////////
//-----STATICS METHODS-----//
/////////////////////////////

Matrix4x4	Matrix4x4::Translate( Matrix4x4 transformationMatrix, Vector3 translation ) {
	float transRaw[16] = {
		1, 0, 0, translation.x,
		0, 1, 0, translation.y,
		0, 0, 1, translation.z,
		0, 0, 0, 1 };
	return Matrix4x4( transRaw ) * transformationMatrix;
}
// Local Rotate
Matrix4x4	Matrix4x4::Rotate( Matrix4x4 transformationMatrix, float angleInRad, Vector3 normalizedVecAxis ) {
	normalizedVecAxis = normalizedVecAxis.normalized();
	float	t = angleInRad;
	float	u = normalizedVecAxis.x;
	float	v = normalizedVecAxis.y;
	float	w = normalizedVecAxis.z;
	float	u2 = u * u;
	float	v2 = v * v;
	float	w2 = w * w;
	float	u2v2w2 = u2 + v2 + w2;

	float a = u2 + ( v2 + w2 ) * cos(t);
	float b = u * v * ( 1 - cos(t) ) - w * sqrt(u2v2w2) * sin(t);
	float c = u * w * ( 1 - cos(t) ) + v * sqrt(u2v2w2) * sin(t);
	float d = u * v * ( 1 - cos(t) ) + w * sqrt(u2v2w2) * sin(t);
	float e = v2 + ( u2 + w2 ) * cos(t);
	float f = v * w * ( 1 - cos(t) ) - u * sqrt(u2v2w2) * sin(t);
	float g = u * w * ( 1 - cos(t) ) - v * sqrt(u2v2w2) * sin(t);
	float h = v * w * ( 1 - cos(t) ) + u * sqrt(u2v2w2) * sin(t);
	float i = w2 + ( u2 + v2 ) * cos(t);

	float _a = transformationMatrix.array[3];
	float _b = transformationMatrix.array[7];
	float _c = transformationMatrix.array[11];

	float x = ( _a * ( v2 + w2 ) - u * ( _b*v + _c*w )) * ( 1 - cos(t) ) + ( _b*w - _c*v ) * sin(t);
	float y = ( _b * ( u2 + w2 ) - v * ( _a*u + _c*w )) * ( 1 - cos(t) ) + ( _c*u - _a*w ) * sin(t);
	float z = ( _c * ( u2 + v2 ) - w * ( _a*u + _b*v )) * ( 1 - cos(t) ) + ( _a*v - _b*u ) * sin(t);

	float	rotRaw[] = {
		a, b, c, x,
		d, e, f, y,
		g, h, i, z,
		0, 0, 0, 1 };
	return Matrix4x4( rotRaw ) * transformationMatrix;
	// from https://sites.google.com/site/glennmurray/glenn-murray-ph-d/rotation-matrices-and-formulas/rotation-about-an-arbitrary-axis-in-3-dimensions
}
// Scale Local
Matrix4x4	Matrix4x4::Scale( Matrix4x4 transformationMatrix, Vector3 scale ) {
	// homemade, a garder un oeil la-dessus
	float	scaleRaw[] = {
		scale.x, 0, 0, transformationMatrix.array[3] * ( 1 - scale.x ),
		0, scale.y, 0, transformationMatrix.array[7] * ( 1 - scale.y ),
		0, 0, scale.z, transformationMatrix.array[11] * ( 1 - scale.z ),
		0, 0, 0, 1 };
	return Matrix4x4( scaleRaw ) * transformationMatrix;
}
Matrix4x4	Matrix4x4::Perspective( float fovy, float aspect, float zNear, float zFar ){

	float rad = fovy;
	float tanHalfFovy = tan(rad / 2);

	float a = 1 / (aspect * tanHalfFovy);
	float b = 1 / (tanHalfFovy);
	float c = - (zFar + zNear) / (zFar - zNear);
	float d = - (2 * zFar * zNear) / (zFar - zNear);
	float e = -1;
	float	persRaw[] = {
		a, 0, 0, 0,
		0, b, 0, 0,
		0, 0, c, d,
		0, 0, e, 0 };
	return Matrix4x4( persRaw );
}
Matrix4x4	Matrix4x4::LookAt( Vector3 eye, Vector3 center, Vector3 up ){
	Vector3 const f( (center - eye).normalized() );
	Vector3 const s( Vector3::Cross(f, up).normalized() );
	Vector3 const u( Vector3::Cross(s, f) );

	float	lookAtRaw[] = {
		 s.x,	 s.y,	 s.z,	-Vector3::Dot(s, eye),
		 u.x,	 u.y,	 u.z,	-Vector3::Dot(u, eye),
		-f.x,	-f.y,	-f.z,	 Vector3::Dot(f, eye),
		 0,		 0,		 0,		 1 };
	return Matrix4x4( lookAtRaw );

}


std::ostream &	operator<<( std::ostream & o, Matrix4x4 const & rhs ) {
	for (int i = 0; i < 4; i++) {
		o << "[ ";
		for (int j = 0; j < 4; j++) {
			o << rhs[ i * 4 + j ] << " ";
		}
		o << "]" << std::endl;
	}
	o << std::endl;
	return o;
}
