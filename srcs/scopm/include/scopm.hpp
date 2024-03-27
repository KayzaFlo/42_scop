#ifndef SCOPM_HPP__
#define SCOPM_HPP__

#include "../src/Vector3.hpp"
#include "../src/Matrix4x4.hpp"

using namespace scopm;

inline float	radians( float deg ) { return deg * ( M_PI / 180 ); }

#include "../../Camera.hpp"
extern Camera	camera;

#endif
