#include "linmath.h"

namespace lm {

template<class T>
T& tvec3<T>::operator[](int i) {
	return values[i];
}

template<class T>
T const & tvec3<T>::operator[](int i) const {
	return values[i];
}

template<class T>
bool tvec3<T>::operator==(tvec3<T> const & v) const {
	return
		values[0] == v[0] &&
		values[1] == v[1] &&
		values[2] == v[2];
}
template<class T>
tvec3<T> & tvec3<T>::operator=(tvec3<T> const & v) {
	values[0] = v[0];
	values[1] = v[1];
	values[2] = v[2];
	return *this;
}

template<class T>
tvec3<T> & tvec3<T>::operator+=(tvec3<T> const & v) {
	values[0] += v[0];
	values[1] += v[1];
	values[2] += v[2];
	return *this;
}

template<class T>
tvec3<T> & tvec3<T>::operator-=(tvec3<T> const & v) {
	values[0] -= v[0];
	values[1] -= v[1];
	values[2] -= v[2];
	return *this;
}


//scalar
template<class T>
tvec3<T> & tvec3<T>::operator=(T s) {
	values[0] = s;
	values[1] = s;
	values[2] = s;
	return *this;
}
template<class T>
tvec3<T> & tvec3<T>::operator+=(T s) {
	values[0] += s;
	values[1] += s;
	values[2] += s;
	return *this;
}
template<class T>
tvec3<T> & tvec3<T>::operator-=(T s) {
	values[0] -= s;
	values[1] -= s;
	values[2] -= s;
	return *this;
}
template<class T>
tvec3<T> & tvec3<T>::operator*=(T s) {
	values[0] *= s;
	values[1] *= s;
	values[2] *= s;
	return *this;
}
template<class T>
tvec3<T> & tvec3<T>::operator/=(T s) {
	values[0] /= s;
	values[1] /= s;
	values[2] /= s;
	return *this;
}

template<class T>
tvec3<T> tvec3<T>::operator+(tvec3<T> const & v) const {
	return tvec3{
		values[0] + v[0],
		values[1] + v[1],
		values[2] + v[2]
	};
}

template<class T>
tvec3<T> tvec3<T>::operator-(tvec3<T> const & v) const {
	return tvec3{
		values[0] + v[0],
		values[1] + v[1],
		values[2] + v[2]
	};
}

template<class T>
tvec3<T> tvec3<T>::operator+(T s) const {
	return tvec3{
		values[0] + s,
		values[1] + s,
		values[2] + s
	};
}
template<class T>
tvec3<T> tvec3<T>::operator-(T s) const {
	return tvec3{
		values[0] - s,
		values[1] - s,
		values[2] - s
	};
}
template<class T>
tvec3<T> tvec3<T>::operator*(T s) const {
	return tvec3{
		values[0] * s,
		values[1] * s,
		values[2] * s
	};
}

template<class T>
tvec3<T> tvec3<T>::operator/(T s) const {
	return tvec3{
		values[0] / s,
		values[1] / s,
		values[2] / s,
	};
}

template struct tvec3<float>;
}