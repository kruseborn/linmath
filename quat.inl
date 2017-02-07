//#include "linmath.h"

namespace lm {
template<typename T>
bool tquat<T>::operator==(tquat<T> const & q) const {
	return
		x == q.x &&
		y == q.y &&
		z == q.z &&
		w == q.w;
}
template<typename T>
tquat<T> & tquat<T>::operator=(tquat<T> const & q) {
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
	return *this;
}
template<typename T>
tquat<T> & tquat<T>::operator+=(tquat<T> const & q) {
	x += q.x;
	y += q.y;
	z += q.z;
	w += q.w;
	return *this;
}
template<typename T>
tquat<T> & tquat<T>::operator-=(tquat<T> const & q) {
	x -= q.x;
	y -= q.y;
	z -= q.z;
	w -= q.w;
	return *this;
}

template<typename T>
tquat<T> & tquat<T>::operator*=(tquat<T> const & q) {
	auto res = *this * q;
	*this = res;
	return *this;
}
template<typename T>
tquat<T> tquat<T>::operator+(tquat<T> const & q) const {
	return tquat<T>{
		x + q.x,
		y + q.y,
		z + q.z,
		w + q.w
	};
}
template<typename T>
tquat<T> tquat<T>::operator-(tquat<T> const & q) const {
	return tquat<T>{
		x - q.x,
			y - q.y,
			z - q.z,
			w - q.w
	};
}
template<typename T>
tquat<T> tquat<T>::operator*(tquat<T> const & q) const {
	tquat<T> res;
	
	res.x = x * q.w + w * q.x + y * q.z - z * q.y;
	res.y = y * q.w + w * q.y + z * q.x - x * q.z;
	res.z = z * q.w + w * q.z + x * q.y - y * q.x;
	res.w = w * q.w - x * q.x - y * q.y - z * q.z;
	return res;
}
template<typename T>
tvec3<T> tquat<T>::operator*(tvec3<T> const & v) const {
	auto qx = this->x, qy = this->y, qz = this->z, qw = this->w;

	auto ix = qw * v.x + qy * v.z - qz * v.y,
		iy = qw * v.y + qz * v.x - qx * v.z,
		iz = qw * v.z + qx * v.y - qy * v.x,
		iw = -qx * x - qy * v.y - qz * v.z;
	tvec3<T> res;
	res.x = ix * qw + iw * -qx + iy * -qz - iz * -qy;
	res.y = iy * qw + iw * -qy + iz * -qx - ix * -qz;
	res.z = iz * qw + iw * -qz + ix * -qy - iy * -qx;
	return res;
}

}
