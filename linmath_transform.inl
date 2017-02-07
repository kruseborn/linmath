//#include "linmath_transform.h"
#include <cassert>
#include <cmath>
#include <limits>
#include <cassert>

namespace lm {

template<typename T>
tmat4<T> mat4_identity() {
	tmat4<T> m;
	m.values[0] = { 1, 0, 0, 0 };
	m.values[1] = { 0, 1, 0, 0 };
	m.values[2] = { 0, 0, 1, 0 };
	m.values[3] = { 0, 0, 0, 1 };
	return m;
}

template<typename T>
tvec2<T> scale(tvec2<T> const & v, T s) {
	return v * s;
}
template<typename T>
tvec3<T> scale(tvec3<T> const & v, T s) {
	return v * s;
}
template<typename T>
tvec4<T> scale(tvec4<T> const & v, T s) {
	return v * s;
}
template<typename T>
T length(tvec2<T> const & v) {
	return sqrt(dot(v, v));
}
template<typename T>
T length(tvec3<T> const & v) {
	return sqrt(dot(v, v));
}
template<typename T>
T length(tvec4<T> const & v) {
	return sqrt(dot(v, v));
}

template<typename T>
tmat4<T> scale(tmat4<T> const & m, tvec3<T> const & v) {
	tmat4<T> result;
	result[0] = m[0] * v[0];
	result[1] = m[1] * v[1];
	result[2] = m[2] * v[2];
	result[3] = m[3];
	return result;
}

template<typename T>
tvec2<T> normalize(tvec2<T> const & v) {
	T k = 1.0f / length(v);
	return v;

}
template<typename T>
tvec3<T> normalize(tvec3<T> const & v) {
	T k = 1.0f / length(v);
	return v * k;
}
template<typename T>
tvec4<T> normalize(tvec4<T> const & v) {
	T k = 1.0f / length(v);
	return v * k;
}
template<typename T>
tmat4<T> normalize(tmat4<T> const & m) {
	tmat4<T> R = m;

	R[2] = normalize(R[2]);

	T s = dot(R[1], R[2]);
	tvec4<T> h = scale(R[2], s);
	R[1] = R[1] - h;
	R[2] = normalize(R[2]);

	s = dot(R[1], R[2]);
	h = scale(R[2], s);
	R[1] = R[1] - h;
	R[1] = normalize(R[1]);

	s = dot(R[0], R[1]);
	h = scale(R[1], s);
	R[0] = R[0] - h;
	R[0] = normalize(R[0]);
	return R;
}

template<typename T>
tmat4<T> translate(tmat4<T> const & m, tvec3<T> const & v) {
	tmat4<T> result(m);
	result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
	return result;
}

template<typename T>
tvec3<T> cross(tvec3<T> const &a, tvec3<T> const &b) {
	tvec3<T> r;
	r[0] = a[1] * b[2] - a[2] * b[1];
	r[1] = a[2] * b[0] - a[0] * b[2];
	r[2] = a[0] * b[1] - a[1] * b[0];
	return r;
}

template<typename T>
T dot(tvec2<T> const &a, tvec2<T> const &b) {
	T res = a[0] * b[0] + a[1] * b[1];
	return res;
}
template<typename T>
T dot(tvec3<T> const &a, tvec3<T> const &b) {
	T res = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	return res;
}
template<typename T>
T dot(tvec4<T> const &a, tvec4<T> const &b) {
	T res = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
	return res;
}

template<typename T>
tmat4<T> transpose(tmat4<T> const  &m) {
	tmat4<T> res;
	for (int j = 0; j<4; ++j)
		for (int i = 0; i<4; ++i)
			res[i][j] = m[j][i];
	return res;
}
template<typename T>
tmat4<T> invert(tmat4<T> const &m) {
	T s[6];
	T c[6];
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
	auto idet = 1.0f / (s[0] * c[5] - s[1] * c[4] + s[2] * c[3] + s[3] * c[2] - s[4] * c[1] + s[5] * c[0]);

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

template<typename T>
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

template<typename T>
tmat4<T> rotateX(tmat4<T> const & M, T angle) {
	T s = sinf(angle);
	T c = cosf(angle);
	tmat4<T> R = {
		1.f, 0.f, 0.f, 0.f,
		0.f,   c,   s, 0.f,
		0.f,  -s,   c, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
	return M * R;
}
template<typename T>
tmat4<T> rotateY(tmat4<T> const & M, T angle)
{
	T s = sinf(angle);
	T c = cosf(angle);
	tmat4<T> R = {
		 c, 0.f,   s, 0.f,
		 0.f, 1.f, 0.f, 0.f,
		 -s, 0.f,   c, 0.f,
		 0.f, 0.f, 0.f, 1.f
	};
	return M * R;
}
template<typename T>
tmat4<T> rotateZ(tmat4<T> const & M, T angle) {
	T s = sinf(angle);
	T c = cosf(angle);
	tmat4<T> R = {
		 c,   s, 0.f, 0.f ,
		 -s,   c, 0.f, 0.f ,
		 0.f, 0.f, 1.f, 0.f ,
		 0.f, 0.f, 0.f, 1.f 
	};
	return M * R;
}

template<typename T>
tmat4<T> orthoLH(T left, T right, T bottom, T top, T zNear, T zFar) {
	tmat4<T> Result = mat4_identity();
	Result[0][0] = 2.0f / (right - left);
	Result[1][1] = 2.0f / (top - bottom);
	Result[3][0] = -(right + left) / (right - left);
	Result[3][1] = -(top + bottom) / (top - bottom);

#		if DEPTH_CLIP_SPACE == DEPTH_ZERO_TO_ONE
	Result[2][2] = 1.0f / (zFar - zNear);
	Result[3][2] = -zNear / (zFar - zNear);
#		else
	Result[2][2] = 2.0f / (zFar - zNear);
	Result[3][2] = -(zFar + zNear) / (zFar - zNear);
#		endif

	return Result;
}

template<typename T>
tmat4<T> orthoRH(T left, T right,T bottom, T top, T zNear, T zFar) {
	tmat4<T> Result = mat4_identity();
	Result[0][0] = 2.0f / (right - left);
	Result[1][1] = 2.0f / (top - bottom);
	Result[3][0] = -(right + left) / (right - left);
	Result[3][1] = -(top + bottom) / (top - bottom);

#		if DEPTH_CLIP_SPACE == DEPTH_ZERO_TO_ONE
	Result[2][2] = -1.0f / (zFar - zNear);
	Result[3][2] = -zNear / (zFar - zNear);
#		else
	Result[2][2] = -2.0f / (zFar - zNear);
	Result[3][2] = -(zFar + zNear) / (zFar - zNear);
#		endif
	return Result;
}

template<typename T>
tmat4<T> ortho(T left, T right, T bottom, T top, T zNear, T zFar) {
#		if COORDINATE_SYSTEM == LEFT_HANDED
	return orthoLH(left, right, bottom, top, zNear, zFar);
#		else
	return orthoRH(left, right, bottom, top, zNear, zFar);
#		endif
}

template<typename T>
tmat4<T> perspective(T fovy, T aspect, T zNear, T zFar) {
#		if COORDINATE_SYSTEM == LEFT_HANDED
	return perspectiveLH(fovy, aspect, zNear, zFar);
#		else
	return perspectiveRH(fovy, aspect, zNear, zFar);
#		endif
}

template<typename T>
tmat4<T> perspectiveRH(T fovy, T aspect, T zNear, T zFar) {
	assert(std::abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

	T const tanHalfFovy = tan(fovy / 2.0f);

	tmat4<T> Result = {};
	Result[0][0] = 1.0f / (aspect * tanHalfFovy);
	Result[1][1] = 1.0f / (tanHalfFovy);
	Result[2][3] = -1.0f;

#		if DEPTH_CLIP_SPACE == DEPTH_ZERO_TO_ONE
	Result[2][2] = zFar / (zNear - zFar);
	Result[3][2] = -(zFar * zNear) / (zFar - zNear);
#		else
	Result[2][2] = -(zFar + zNear) / (zFar - zNear);
	Result[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
#		endif

	return Result;
}

template<typename T>
tmat4<T> perspectiveLH(T fovy, T aspect, T zNear, T zFar) {
	assert(std::abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

	T const tanHalfFovy = tan(fovy / 2.0f);

	tmat4<T> Result = {};
	Result[0][0] = 1.0f / (aspect * tanHalfFovy);
	Result[1][1] = 1.0f / (tanHalfFovy);
	Result[2][3] = 1.0f;

#		if DEPTH_CLIP_SPACE == DEPTH_ZERO_TO_ONE
	Result[2][2] = zFar / (zFar - zNear);
	Result[3][2] = -(zFar * zNear) / (zFar - zNear);
#		else
	Result[2][2] = (zFar + zNear) / (zFar - zNear);
	Result[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
#		endif

	return Result;
}

template<typename T>
tmat4<T> lookAtRH(tvec3<T> const & eye, tvec3<T> const & center, tvec3<T> const & up) {
	tvec3<T> const f(normalize(center - eye));
	tvec3<T> const s(normalize(cross(f, up)));
	tvec3<T> const u(cross(s, f));

	tmat4<T> Result = mat4_identity();
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

template<typename T>
tmat4<T> lookAtLH(tvec3<T> const & eye, tvec3<T> const & center, tvec3<T> const & up) {
	tvec3<T> const f(normalize(center - eye));
	tvec3<T> const s(normalize(cross(up, f)));
	tvec3<T> const u(cross(f, s));

	tmat4<T> Result = mat4_identity();
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

template<typename T>
tmat4<T> lookAt(tvec3<T> const & eye, tvec3<T> const & center, tvec3<T> const & up) {
#		if COORDINATE_SYSTEM == LEFT_HANDED
	return lookAtLH(eye, center, up);
#		else
	return lookAtRH(eye, center, up);
#		endif
}

template<typename T>
tvec3<T> unProject(
	tvec3<T> const & win,
	tmat4<T> const & model,
	tmat4<T> const & proj,
	tvec4<T> const & viewport
)
{
	tmat4<T> Inverse = invert(proj * model);

	tvec4<T> tmp = tvec4<T>{ win.x, win.y, win.z, T(1) };
	tmp.x = (tmp.x - T(viewport[0])) / T(viewport[2]);
	tmp.y = (tmp.y - T(viewport[1])) / T(viewport[3]);
#		if DEPTH_CLIP_SPACE == DEPTH_ZERO_TO_ONE
	tmp.x = tmp.x * 2.0f - 1.0f;
	tmp.y = tmp.y * 2.0f - 1.0f;
#		else
	tmp = tmp * 2.0f - 1.0f;
#		endif

	tvec4<T> obj = Inverse * tmp;
	obj /= obj.w;

	return tvec3<T>{obj.x, obj.y, obj.z};
}

template<typename T>
tvec3<T> project(
	tvec3<T> const & obj,
	tmat4<T> const & model,
	tmat4<T> const & proj,
	tvec4<T> const & viewport
)
{
	tvec4<T> tmp = tvec4<T>{ obj.x, obj.y, obj.z, T(1) };
	tmp = model * tmp;
	tmp = proj * tmp;

	tmp /= tmp.w;
#		if DEPTH_CLIP_SPACE == DEPTH_ZERO_TO_ONE
	tmp.x = tmp.x * 0.5f + 0.5f;
	tmp.y = tmp.y * 0.5f + 0.5f;
#		else
	tmp = tmp * 0.5f + 0.5f;
#		endif
	tmp[0] = tmp[0] * T(viewport[2]) + T(viewport[0]);
	tmp[1] = tmp[1] * T(viewport[3]) + T(viewport[1]);

	return tvec3<T>{tmp.x, tmp.y, tmp.z};
}
template<typename T>
T distance(tvec3<T> const &p0, tvec3<T> const &p1) {
	return length(p1 - p0);
}
template<typename T>
tvec4<T> abs(tvec4<T> const &vec) {
	return tvec4<T>{std::abs(vec.x), std::abs(vec.y), std::abs(vec.z), std::abs(vec.w)};
}
template<typename T>
tvec3<T> abs(tvec3<T> const &vec) {
	return tvec3<T>{std::abs(vec.x), std::abs(vec.y), std::abs(vec.z)};
}
template<typename T>
tvec2<T> abs(tvec2<T> const &vec) {
	return tvec2<T>{std::abs(vec.x), std::abs(vec.y)};
}

template<typename T>
tquat<T> quat_identity() {
	return tquat<T>{ 0,0,0,1 };
}
template<typename T>
tquat<T> setAxisAngle(tvec3<T> axis, T rad) {
	tquat<T> res;
	rad = rad * 0.5f;
	auto s = sin(rad);
	res.x = s * axis.x;
	res.y = s * axis.y;
	res.z = s * axis.z;
	res.w = cos(rad);
	return res;
}
template<typename T>
tquat<T> rotateX(tquat<T> const &q, T rad) {
	tquat<T> res;
	rad *= 0.5f;

	auto ax = q.x, ay = q.y, az = q.z, aw = q.w;
	auto bx = sin(rad), bw = cos(rad);

	res.x = ax * bw + aw * bx;
	res.y = ay * bw + az * bx;
	res.z = az * bw - ay * bx;
	res.w = aw * bw - ax * bx;
	return res;
}
template<typename T>
tquat<T> rotateY(tquat<T> const &q, T rad) {
	tquat<T> res;
	rad *= 0.5f;

	auto ax = q.x, ay = q.y, az = q.z, aw = q.w;
	auto by = sin(rad), bw = cos(rad);

	res.x = ax * bw - az * by;
	res.y = ay * bw + aw * by;
	res.z = az * bw + ax * by;
	res.w = aw * bw - ay * by;
	return res;
}
template<typename T>
tquat<T> rotateZ(tquat<T> const &q, T rad) {
	tquat<T> res;
	rad *= 0.5f;

	auto ax = q.x, ay = q.y, az = q.z, aw = q.w;
	auto bz = sin(rad), bw = cos(rad);

	res.x = ax * bw + ay * bz;
	res.y = ay * bw - ax * bz;
	res.z = az * bw + aw * bz;
	res.w = aw * bw - az * bz;
	return res;
}

template<typename T>
tmat4<T> toMatrix(tquat<T> const &q) {
	tmat4<T> M = {};
	T a = q.w;
	T b = q.x;
	T c = q.y;
	T d = q.z;
	T a2 = a*a;
	T b2 = b*b;
	T c2 = c*c;
	T d2 = d*d;

	M[0][0] = a2 + b2 - c2 - d2;
	M[0][1] = 2.f*(b*c + a*d);
	M[0][2] = 2.f*(b*d - a*c);
	M[0][3] = 0.f;

	M[1][0] = 2 * (b*c - a*d);
	M[1][1] = a2 - b2 + c2 - d2;
	M[1][2] = 2.f*(c*d + a*b);
	M[1][3] = 0.f;

	M[2][0] = 2.f*(b*d + a*c);
	M[2][1] = 2.f*(c*d - a*b);
	M[2][2] = a2 - b2 - c2 + d2;
	M[2][3] = 0.f;

	M[3][0] = M[3][1] = M[3][2] = 0.f;
	M[3][3] = 1.f;
	return M;
}
} //lm
