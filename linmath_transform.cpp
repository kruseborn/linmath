#include "linmath_transform.h"
#include <cmath>
#include <limits>
#include <cassert>

template<class T>
tmat4<T> mat4_identity() {
	tmat4<T> m;
	m.values[0] = { 1, 0, 0, 0 };
	m.values[1] = { 0, 1, 0, 0 };
	m.values[2] = { 0, 0, 1, 0 };
	m.values[3] = { 0, 0, 0, 1 };
	return m;
}

template<class T>
tvec2<T> scale(tvec2<T> const & v, T s) {
	return v * s;
}
template <class T>
tvec3<T> scale(tvec3<T> const & v, T s) {
	return v * s;
}
template <class T>
tvec4<T> scale(tvec4<T> const & v, T s) {
	return v * s;
}
template <class T>
T length(tvec2<T> const & v) {
	return sqrt(dot(v, v));
}
template <class T>
T length(tvec3<T> const & v) {
	return sqrt(dot(v, v));
}
template <class T>
T length(tvec4<T> const & v) {
	return sqrt(dot(v, v));
}

template <class T>
tmat4<T> scale(tmat4<T> const & m, tvec3<T> const & v) {
	tmat4<T> result;
	result[0] = m[0] * v[0];
	result[1] = m[1] * v[1];
	result[2] = m[2] * v[2];
	result[3] = m[3];
	return result;
}

template <class T>
tvec2<T> normalize(tvec2<T> const & v) {
	T k = static_cast<T>(1) / length<T>(v);
	return v;

}
template <class T>
tvec3<T> normalize(tvec3<T> const & v) {
	T k = static_cast<T>(1) / length(v);
	return v * k;
}
template <class T>
tvec4<T> normalize(tvec4<T> const & v) {
	T k = static_cast<T>(1) / length(v);
	return v * k;
}
template <class T>
tmat4<T> normalize(tmat4<T> const & m) {
	tmat4<T> R = m;

	R[2] = normalize<T>(R[2]);

	T s = dot<T>(R[1], R[2]);
	tvec4<T> h = scale<T>(R[2], s);
	R[1] = R[1] - h;
	R[2] = normalize<T>(R[2]);

	s = dot<T>(R[1], R[2]);
	h = scale<T>(R[2], s);
	R[1] = R[1] - h;
	R[1] = normalize<T>(R[1]);

	s = dot<T>(R[0], R[1]);
	h = scale<T>(R[1], s);
	R[0] = R[0] - h;
	R[0] = normalize<T>(R[0]);
	return R;
}

template <class T>
tmat4<T> translate(tmat4<T> const & m, tvec3<T> const & v) {
	tmat4<T> result(m);
	result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
	return result;
}

template<class T>
tvec3<T> cross(tvec3<T> const &a, tvec3<T> const &b) {
	tvec3<T> r;
	r[0] = a[1] * b[2] - a[2] * b[1];
	r[1] = a[2] * b[0] - a[0] * b[2];
	r[2] = a[0] * b[1] - a[1] * b[0];
	return r;
}

template<class T>
T dot(tvec2<T> const &a, tvec2<T> const &b) {
	T res = a[0] * b[0] + a[1] * b[1];
	return res;
}
template<class T>
T dot(tvec3<T> const &a, tvec3<T> const &b) {
	T res = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	return res;
}
template<class T>
T dot(tvec4<T> const &a, tvec4<T> const &b) {
	T res = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
	return res;
}

template<class T>
tmat4<T> transpose(tmat4<T> const  &m) {
	tmat4<T> res;
	for (int j = 0; j<4; ++j)
		for (int i = 0; i<4; ++i)
			res[i][j] = m[j][i];
	return res;
}
template<class T>
tmat4<T> invert(tmat4<T> const &m) {
	float s[6];
	float c[6];
	tmat4<T> res;

	s[0] = m[0][0] * m[1][1] - m[1][0] * m[0][1];
	s[1] = m[0][0] * m[1][2] - m[1][0] * m[0][2];
	s[2] = m[0][0] * m[1][3] - m[1][0] * m[0][3];
	s[3] = m[0][1] * m[1][2] - m[1][1] * m[0][2];
	s[4] = m[0][1] * m[1][3] - m[1][1] * m[0][3];
	s[5] = m[0][2] * m[1][3] - m[1][2] * m[0][3];

	c[0] = m[2][0] * m[3][1] - m[3][0] * m[2][1];
	c[1] = m[2][0] * m[3][2] - m[3][0] * m[2][2];
	c[2] = m[2][0] * m[3][3] - m[3][0] * m[2][3];
	c[3] = m[2][1] * m[3][2] - m[3][1] * m[2][2];
	c[4] = m[2][1] * m[3][3] - m[3][1] * m[2][3];
	c[5] = m[2][2] * m[3][3] - m[3][2] * m[2][3];

	/* Assumes it is invertible */
	auto idet = static_cast<T>(1) / (s[0] * c[5] - s[1] * c[4] + s[2] * c[3] + s[3] * c[2] - s[4] * c[1] + s[5] * c[0]);

	res[0][0] = (m[1][1] * c[5] - m[1][2] * c[4] + m[1][3] * c[3]) * idet;
	res[0][1] = (-m[0][1] * c[5] + m[0][2] * c[4] - m[0][3] * c[3]) * idet;
	res[0][2] = (m[3][1] * s[5] - m[3][2] * s[4] + m[3][3] * s[3]) * idet;
	res[0][3] = (-m[2][1] * s[5] + m[2][2] * s[4] - m[2][3] * s[3]) * idet;

	res[1][0] = (-m[1][0] * c[5] + m[1][2] * c[2] - m[1][3] * c[1]) * idet;
	res[1][1] = (m[0][0] * c[5] - m[0][2] * c[2] + m[0][3] * c[1]) * idet;
	res[1][2] = (-m[3][0] * s[5] + m[3][2] * s[2] - m[3][3] * s[1]) * idet;
	res[1][3] = (m[2][0] * s[5] - m[2][2] * s[2] + m[2][3] * s[1]) * idet;

	res[2][0] = (m[1][0] * c[4] - m[1][1] * c[2] + m[1][3] * c[0]) * idet;
	res[2][1] = (-m[0][0] * c[4] + m[0][1] * c[2] - m[0][3] * c[0]) * idet;
	res[2][2] = (m[3][0] * s[4] - m[3][1] * s[2] + m[3][3] * s[0]) * idet;
	res[2][3] = (-m[2][0] * s[4] + m[2][1] * s[2] - m[2][3] * s[0]) * idet;

	res[3][0] = (-m[1][0] * c[3] + m[1][1] * c[1] - m[1][2] * c[0]) * idet;
	res[3][1] = (m[0][0] * c[3] - m[0][1] * c[1] + m[0][2] * c[0]) * idet;
	res[3][2] = (-m[3][0] * s[3] + m[3][1] * s[1] - m[3][2] * s[0]) * idet;
	res[3][3] = (m[2][0] * s[3] - m[2][1] * s[1] + m[2][2] * s[0]) * idet;
	return res;
}

template <class T>
tmat4<T> rotate(tmat4<T> const & m, T angle, tvec3<T> const & v) {
	T const a = angle;
	T const c = cos(a);
	T const s = sin(a);

	tvec3<T> axis(normalize(v));
	tvec3<T> temp(axis * (T(1) - c));

	tmat4<T> rotate;
	rotate[0][0] = c + temp[0] * axis[0];
	rotate[0][1] = temp[0] * axis[1] + s * axis[2];
	rotate[0][2] = temp[0] * axis[2] - s * axis[1];

	rotate[1][0] = temp[1] * axis[0] - s * axis[2];
	rotate[1][1] = c + temp[1] * axis[1];
	rotate[1][2] = temp[1] * axis[2] + s * axis[0];

	rotate[2][0] = temp[2] * axis[0] + s * axis[1];
	rotate[2][1] = temp[2] * axis[1] - s * axis[0];
	rotate[2][2] = c + temp[2] * axis[2];

	tmat4<T> result;
	result[0] = m[0] * rotate[0][0] + m[1] * rotate[0][1] + m[2] * rotate[0][2];
	result[1] = m[0] * rotate[1][0] + m[1] * rotate[1][1] + m[2] * rotate[1][2];
	result[2] = m[0] * rotate[2][0] + m[1] * rotate[2][1] + m[2] * rotate[2][2];
	result[3] = m[3];
	return result;
}

template<class T>
tmat4<T> rotateX(tmat4<T> const & M, float angle) {
	float s = sinf(angle);
	float c = cosf(angle);
	tmat4<T> R = {
		1.f, 0.f, 0.f, 0.f,
		0.f,   c,   s, 0.f,
		0.f,  -s,   c, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
	return M * R;
}
template<class T>
tmat4<T> rotateY(tmat4<T> const & M, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	tmat4<T> R = {
		 c, 0.f,   s, 0.f,
		 0.f, 1.f, 0.f, 0.f,
		 -s, 0.f,   c, 0.f,
		 0.f, 0.f, 0.f, 1.f
	};
	return M * R;
}
template<class T>
tmat4<T> rotateZ(tmat4<T> const & M, float angle) {
	float s = sinf(angle);
	float c = cosf(angle);
	tmat4<T> R = {
		 c,   s, 0.f, 0.f ,
		 -s,   c, 0.f, 0.f ,
		 0.f, 0.f, 1.f, 0.f ,
		 0.f, 0.f, 0.f, 1.f 
	};
	return M * R;
}


template <class T>
static tmat4<T> orthoLH(T left, T right, T bottom, T top, T zNear, T zFar) {
	tmat4<T> Result(1);
	Result[0][0] = static_cast<T>(2) / (right - left);
	Result[1][1] = static_cast<T>(2) / (top - bottom);
	Result[3][0] = -(right + left) / (right - left);
	Result[3][1] = -(top + bottom) / (top - bottom);

#		if DEPTH_CLIP_SPACE == DEPTH_ZERO_TO_ONE
	Result[2][2] = static_cast<T>(1) / (zFar - zNear);
	Result[3][2] = -zNear / (zFar - zNear);
#		else
	Result[2][2] = static_cast<T>(2) / (zFar - zNear);
	Result[3][2] = -(zFar + zNear) / (zFar - zNear);
#		endif

	return Result;
}

template <class T>
static tmat4<T> orthoRH(T left, T right,T bottom, T top, T zNear, T zFar) {
	tmat4<T> Result = mat4_identity<T>();
	Result[0][0] = static_cast<T>(2) / (right - left);
	Result[1][1] = static_cast<T>(2) / (top - bottom);
	Result[3][0] = -(right + left) / (right - left);
	Result[3][1] = -(top + bottom) / (top - bottom);

#		if DEPTH_CLIP_SPACE == DEPTH_ZERO_TO_ONE
	Result[2][2] = -static_cast<T>(1) / (zFar - zNear);
	Result[3][2] = -zNear / (zFar - zNear);
#		else
	Result[2][2] = -static_cast<T>(2) / (zFar - zNear);
	Result[3][2] = -(zFar + zNear) / (zFar - zNear);
#		endif
	return Result;
}

template <class T>
tmat4<T> ortho(T left, T right, T bottom, T top, T zNear, T zFar) {
#		if COORDINATE_SYSTEM == LEFT_HANDED
	return orthoLH(left, right, bottom, top, zNear, zFar);
#		else
	return orthoRH(left, right, bottom, top, zNear, zFar);
#		endif
}

template <typename T>
tmat4<T> perspective(T fovy, T aspect, T zNear, T zFar) {
#		if COORDINATE_SYSTEM == LEFT_HANDED
	return perspectiveLH(fovy, aspect, zNear, zFar);
#		else
	return perspectiveRH(fovy, aspect, zNear, zFar);
#		endif
}

template <typename T>
tmat4<T> perspectiveRH(T fovy, T aspect, T zNear, T zFar) {
	assert(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

	T const tanHalfFovy = tan(fovy / static_cast<T>(2));

	tmat4<T> Result = {};
	Result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
	Result[1][1] = static_cast<T>(1) / (tanHalfFovy);
	Result[2][3] = -static_cast<T>(1);

#		if DEPTH_CLIP_SPACE == DEPTH_ZERO_TO_ONE
	Result[2][2] = zFar / (zNear - zFar);
	Result[3][2] = -(zFar * zNear) / (zFar - zNear);
#		else
	Result[2][2] = -(zFar + zNear) / (zFar - zNear);
	Result[3][2] = -(static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
#		endif

	return Result;
}

template <typename T>
tmat4<T> perspectiveLH(T fovy, T aspect, T zNear, T zFar) {
	assert(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

	T const tanHalfFovy = tan(fovy / static_cast<T>(2));

	tmat4<T> Result(static_cast<T>(0));
	Result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
	Result[1][1] = static_cast<T>(1) / (tanHalfFovy);
	Result[2][3] = static_cast<T>(1);

#		if DEPTH_CLIP_SPACE == DEPTH_ZERO_TO_ONE
	Result[2][2] = zFar / (zFar - zNear);
	Result[3][2] = -(zFar * zNear) / (zFar - zNear);
#		else
	Result[2][2] = (zFar + zNear) / (zFar - zNear);
	Result[3][2] = -(static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
#		endif

	return Result;
}

template <typename T>
static tmat4<T> lookAtRH(tvec3<T> const & eye, tvec3<T> const & center, tvec3<T> const & up) {
	tvec3<T> const f(normalize(center - eye));
	tvec3<T> const s(normalize(cross(f, up)));
	tvec3<T> const u(cross(s, f));

	tmat4<T> Result = mat4_identity<T>();
	Result[0][0] = s.x;
	Result[1][0] = s.y;
	Result[2][0] = s.z;
	Result[0][1] = u.x;
	Result[1][1] = u.y;
	Result[2][1] = u.z;
	Result[0][2] = -f.x;
	Result[1][2] = -f.y;
	Result[2][2] = -f.z;
	Result[3][0] = -dot(s, eye);
	Result[3][1] = -dot(u, eye);
	Result[3][2] = dot(f, eye);
	return Result;
}

template <typename T>
static tmat4<T> lookAtLH(tvec3<T> const & eye, tvec3<T> const & center, tvec3<T> const & up) {
	tvec3<T> const f(normalize(center - eye));
	tvec3<T> const s(normalize(cross(up, f)));
	tvec3<T> const u(cross(f, s));

	tmat4<T> Result(1);
	Result[0][0] = s.x;
	Result[1][0] = s.y;
	Result[2][0] = s.z;
	Result[0][1] = u.x;
	Result[1][1] = u.y;
	Result[2][1] = u.z;
	Result[0][2] = f.x;
	Result[1][2] = f.y;
	Result[2][2] = f.z;
	Result[3][0] = -dot(s, eye);
	Result[3][1] = -dot(u, eye);
	Result[3][2] = -dot(f, eye);
	return Result;
}


template <typename T>
tmat4<T> lookAt(tvec3<T> const & eye, tvec3<T> const & center, tvec3<T> const & up) {
#		if COORDINATE_SYSTEM == LEFT_HANDED
	return lookAtLH(eye, center, up);
#		else
	return lookAtRH(eye, center, up);
#		endif
}

template tmat4<float> mat4_identity();
template tvec2<float> scale(tvec2<float> const & v, float s);
template tvec3<float> scale(tvec3<float> const & v, float s);
template tvec4<float> scale(tvec4<float> const & m, float s);
template tmat4<float> scale(tmat4<float> const & m, tvec3<float> const & v);
template float length(tvec2<float> const & v);
template float length(tvec3<float> const & v);
template float length(tvec4<float> const & m);
template tvec2<float> normalize(tvec2<float> const & v);
template tvec3<float> normalize(tvec3<float> const & v);
template tvec4<float> normalize(tvec4<float> const & m);
template tmat4<float> normalize(tmat4<float> const & m);
template tmat4<float> translate(tmat4<float> const & m, tvec3<float> const & v);
template tvec3<float> cross(tvec3<float> const &a, tvec3<float> const &b);
template float dot(tvec2<float> const &a, tvec2<float> const &b);
template float dot(tvec3<float> const &a, tvec3<float> const &b);
template float dot(tvec4<float> const &a, tvec4<float> const &b);
template tmat4<float> transpose(tmat4<float> const  &m);
template tmat4<float> invert(tmat4<float> const &m);
template tmat4<float> rotate(tmat4<float> const & m, float angle, tvec3<float> const & v);
template tmat4<float> rotateX(tmat4<float> const & M, float angle);
template tmat4<float> rotateY(tmat4<float> const & M, float angle);
template tmat4<float> rotateZ(tmat4<float> const & M, float angle);
template tmat4<float> ortho(float left, float right, float bottom, float top, float zNear, float zFar);
template tmat4<float> perspective(float fovy, float aspect, float zNear, float zFar);
template tmat4<float> lookAt(tvec3<float> const & eye, tvec3<float> const & center, tvec3<float> const & up);
