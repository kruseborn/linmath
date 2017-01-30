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

template <class T> tmat4<T> mat4_identity();
template <class T> tvec2<T> scale(tvec2<T> const & v, T s);
template <class T> tvec3<T> scale(tvec3<T> const & v, T s);
template <class T> tvec4<T> scale(tvec4<T> const & m, T s);
template <class T> tmat4<T> scale(tmat4<T> const & m, tvec3<T> const & v);
template <class T> T length(tvec2<T> const & v);
template <class T> T length(tvec3<T> const & v);
template <class T> T length(tvec4<T> const & m);
template <class T> tvec2<T> normalize(tvec2<T> const & v);
template <class T> tvec3<T> normalize(tvec3<T> const & v);
template <class T> tvec4<T> normalize(tvec4<T> const & m);
template <class T> tmat4<T> normalize(tmat4<T> const & m);
template <class T> tmat4<T> translate(tmat4<T> const & m, tvec3<T> const & v);
template<class T> tvec3<T> cross(tvec3<T> const &a, tvec3<T> const &b);
template<class T> T dot(tvec2<T> const &a, tvec2<T> const &b);
template<class T> T dot(tvec3<T> const &a, tvec3<T> const &b);
template<class T> T dot(tvec4<T> const &a, tvec4<T> const &b);
template<class T> tmat4<T> transpose(tmat4<T> const  &m);
template<class T> tmat4<T> invert(tmat4<T> const &m);
template <class T> tmat4<T> rotate(tmat4<T> const & m, T angle, tvec3<T> const & v);
template<class T> tmat4<T> rotateX(tmat4<T> const & M, float angle);
template<class T> tmat4<T> rotateY(tmat4<T> const & M, float angle);
template<class T> tmat4<T> rotateZ(tmat4<T> const & M, float angle);
template <class T> tmat4<T> ortho(T left, T right, T bottom, T top, T zNear, T zFar);
template<class T> tmat4<T> perspective(T fovy, T aspect, T zNear, T zFar);
template <typename T> tmat4<T> lookAt(tvec3<T> const & eye, tvec3<T> const & center, tvec3<T> const & up);


extern template tmat4<float> mat4_identity();
extern template tvec2<float> scale(tvec2<float> const & v, float s);
extern template tvec3<float> scale(tvec3<float> const & v, float s);
extern template tvec4<float> scale(tvec4<float> const & m, float s);
extern template tmat4<float> scale(tmat4<float> const & m, tvec3<float> const & v);
extern template float length(tvec2<float> const & v);
extern template float length(tvec3<float> const & v);
extern template float length(tvec4<float> const & m);
extern template tvec2<float> normalize(tvec2<float> const & v);
extern template tvec3<float> normalize(tvec3<float> const & v);
extern template tvec4<float> normalize(tvec4<float> const & m);
extern template tmat4<float> normalize(tmat4<float> const & m);
extern template tmat4<float> translate(tmat4<float> const & m, tvec3<float> const & v);
extern template tvec3<float> cross(tvec3<float> const &a, tvec3<float> const &b);
extern template float dot(tvec2<float> const &a, tvec2<float> const &b);
extern template float dot(tvec3<float> const &a, tvec3<float> const &b);
extern template float dot(tvec4<float> const &a, tvec4<float> const &b);
extern template tmat4<float> transpose(tmat4<float> const  &m);
extern template tmat4<float> invert(tmat4<float> const &m);
extern template tmat4<float> rotate(tmat4<float> const & m, float angle, tvec3<float> const & v);
extern template tmat4<float> rotateX(tmat4<float> const & M, float angle);
extern template tmat4<float> rotateY(tmat4<float> const & M, float angle);
extern template tmat4<float> rotateZ(tmat4<float> const & M, float angle);
extern template tmat4<float> ortho(float left, float right, float bottom, float top, float zNear, float zFar);
extern template tmat4<float> perspective(float fovy, float aspect, float zNear, float zFar);
extern template tmat4<float> lookAt(tvec3<float> const & eye, tvec3<float> const & center, tvec3<float> const & up);
