#pragma once
#include "linmath.h"

#define LEFT_HANDED				0x00000001	// For DirectX, Metal, Vulkan
#define RIGHT_HANDED			0x00000002	// For OpenGL

#ifdef FORCE_LEFT_HANDED
#	define COORDINATE_SYSTEM LEFT_HANDED
#else
#	define COORDINATE_SYSTEM RIGHT_HANDED
#endif

#define DEPTH_ZERO_TO_ONE				0x00000001 // Vulkan
#define DEPTH_NEGATIVE_ONE_TO_ONE		0x00000002  // OpenGL, DirectX, Metal

#ifdef FORCE_DEPTH_ZERO_TO_ONE
#	define DEPTH_CLIP_SPACE DEPTH_ZERO_TO_ONE
#else
#	define DEPTH_CLIP_SPACE DEPTH_NEGATIVE_ONE_TO_ONE
#endif

namespace lm {


template<typename T> tmat4<T> mat4_identity();
template<typename T> tvec2<T> scale(tvec2<T> const & v, T s);
template<typename T> tvec3<T> scale(tvec3<T> const & v, T s);
template<typename T> tvec4<T> scale(tvec4<T> const & m, T s);
template<typename T> tmat4<T> scale(tmat4<T> const & m, tvec3<T> const & v);
template<typename T> T length(tvec2<T> const & v);
template<typename T> T length(tvec3<T> const & v);
template<typename T> T length(tvec4<T> const & m);
template<typename T> tvec2<T> normalize(tvec2<T> const & v);
template<typename T> tvec3<T> normalize(tvec3<T> const & v);
template<typename T> tvec4<T> normalize(tvec4<T> const & m);
template<typename T> tmat4<T> normalize(tmat4<T> const & m);
template<typename T> tmat4<T> translate(tmat4<T> const & m, tvec3<T> const & v);
template<typename T> tvec3<T> cross(tvec3<T> const &a, tvec3<T> const &b);
template<typename T> T dot(tvec2<T> const &a, tvec2<T> const &b);
template<typename T> T dot(tvec3<T> const &a, tvec3<T> const &b);
template<typename T> T dot(tvec4<T> const &a, tvec4<T> const &b);
template<typename T> tmat4<T> transpose(tmat4<T> const  &m);
template<typename T> tmat4<T> invert(tmat4<T> const &m);
template<typename T> tmat4<T> rotate(tmat4<T> const & m, T angle, tvec3<T> const & v);
template<typename T> tmat4<T> rotateX(tmat4<T> const & M, T angle);
template<typename T> tmat4<T> rotateY(tmat4<T> const & M, T angle);
template<typename T> tmat4<T> rotateZ(tmat4<T> const & M, T angle);
template<typename T> tmat4<T> ortho(T left, T right, T bottom, T top, T zNear, T zFar);
template<typename T> tmat4<T> perspective(T fovy, T aspect, T zNear, T zFar);
template<typename T> tmat4<T> lookAt(tvec3<T> const & eye, tvec3<T> const & center, tvec3<T> const & up);
template<typename T> tvec3<T> unProject(tvec3<T> const & win, tmat4<T> const & model, tmat4<T> const & proj, tvec4<T> const & viewport);
template<typename T> tvec3<T> project(tvec3<T> const & obj, tmat4<T> const & model, tmat4<T> const & proj, tvec4<T> const & viewport);
template<typename T> T distance(tvec3<T> const & p0, tvec3<T> const & p1);
template<typename T> tvec4<T> abs(tvec4<T> const &vec);
template<typename T> tvec3<T> abs(tvec3<T> const &vec);
template<typename T> tvec2<T> abs(tvec2<T> const &vec);
template<typename T> tmat4<T> lookAtLH(tvec3<T> const & eye, tvec3<T> const & center, tvec3<T> const & up);
template<typename T> tmat4<T> lookAtRH(tvec3<T> const & eye, tvec3<T> const & center, tvec3<T> const & up);
template<typename T> tmat4<T> orthoRH(T left, T right, T bottom, T top, T zNear, T zFar);
template<typename T> tmat4<T> orthoLH(T left, T right, T bottom, T top, T zNear, T zFar);
template<typename T> tmat4<T> perspectiveLH(T fovy, T aspect, T zNear, T zFar);
template<typename T> tmat4<T> perspectiveRH(T fovy, T aspect, T zNear, T zFar);

template<typename T> tquat<T> quat_identity();
template<typename T> tquat<T> setAxisAngle(tvec3<T> axis, T rad);
template<typename T> tquat<T> rotateX(tquat<T> const &q, T rad);
template<typename T> tquat<T> rotateY(tquat<T> const &q, T rad);
template<typename T> tquat<T> rotateZ(tquat<T> const &q, T rad);
template<typename T> tmat4<T> toMatrix(tquat<T> const &q);
template<typename T> T radians(T degrees);

}
#include "linmath_transform.inl"
