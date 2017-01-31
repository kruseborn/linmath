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

template <typename T> tmat4<T> mat4_identity();
template <typename T> tvec2<T> scale(tvec2<T> const & v, T s);
template <typename T> tvec3<T> scale(tvec3<T> const & v, T s);
template <typename T> tvec4<T> scale(tvec4<T> const & m, T s);
template <typename T> tmat4<T> scale(tmat4<T> const & m, tvec3<T> const & v);
template <typename T> T length(tvec2<T> const & v);
template <typename T> T length(tvec3<T> const & v);
template <typename T> T length(tvec4<T> const & m);
template <typename T> tvec2<T> normalize(tvec2<T> const & v);
template <typename T> tvec3<T> normalize(tvec3<T> const & v);
template <typename T> tvec4<T> normalize(tvec4<T> const & m);
template <typename T> tmat4<T> normalize(tmat4<T> const & m);
template <typename T> tmat4<T> translate(tmat4<T> const & m, tvec3<T> const & v);
template<typename T> tvec3<T> cross(tvec3<T> const &a, tvec3<T> const &b);
template<typename T> T dot(tvec2<T> const &a, tvec2<T> const &b);
template<typename T> T dot(tvec3<T> const &a, tvec3<T> const &b);
template<typename T> T dot(tvec4<T> const &a, tvec4<T> const &b);
template<typename T> tmat4<T> transpose(tmat4<T> const  &m);
template<typename T> tmat4<T> invert(tmat4<T> const &m);
template <typename T> tmat4<T> rotate(tmat4<T> const & m, T angle, tvec3<T> const & v);
template<typename T> tmat4<T> rotateX(tmat4<T> const & M, float angle);
template<typename T> tmat4<T> rotateY(tmat4<T> const & M, float angle);
template<typename T> tmat4<T> rotateZ(tmat4<T> const & M, float angle);
template <typename T> tmat4<T> ortho(T left, T right, T bottom, T top, T zNear, T zFar);
template <typename T> tmat4<T> perspective(T fovy, T aspect, T zNear, T zFar);
template <typename T> tmat4<T> lookAt(tvec3<T> const & eye, tvec3<T> const & center, tvec3<T> const & up);
template <typename T> tvec3<T> unProject(tvec3<T> const & win, tmat4<T> const & model, tmat4<T> const & proj, tvec4<T> const & viewport);
template <typename T> tmat4<T> call(tmat4<T> const& m);
template <typename T> tvec3<T> project(tvec3<T> const & obj, tmat4<T> const & model, tmat4<T> const & proj, tvec4<T> const & viewport);
template<typename T> T distance(tvec3<T> const & p0, tvec3<T> const & p1);
template<typename T> tvec4<T> abs(tvec4<T> const &vec);
template<typename T> tvec3<T> abs(tvec3<T> const &vec);
template<typename T> tvec2<T> abs(tvec2<T> const &vec);

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
extern template tvec3<float> unProject(tvec3<float> const & win, tmat4<float> const & model, tmat4<float> const & proj, tvec4<float> const & viewport);
extern template tmat4<float> call(tmat4<float> const& m);
extern template tvec3<float> project(tvec3<float> const & obj, tmat4<float> const & model, tmat4<float> const & proj, tvec4<float> const & viewport);
extern template float distance(tvec3<float> const & p0, tvec3<float> const & p1);
extern template tvec4<float> abs(tvec4<float> const &vec);
extern template tvec3<float> abs(tvec3<float> const &vec);
extern template tvec2<float> abs(tvec2<float> const &vec);

}