#include "linmath.h"

namespace lm {

template<class T>
T& tvec4<T>::operator[](int i) {
	return values[i];
}

template<class T>
T const & tvec4<T>::operator[](int i) const {
	return values[i];
}
template<class T>
bool tvec4<T>::operator==(tvec4<T> const & v) const {
	return
		values[0] == v[0] &&
		values[1] == v[1] &&
		values[2] == v[2] &&
		values[3] == v[3];
}

template<class T>
tvec4<T> & tvec4<T>::operator=(tvec4<T> const & v) {
	values[0] = v[0];
	values[1] = v[1];
	values[2] = v[2];
	values[3] = v[3];
	return *this;
}

template<class T>
tvec4<T> & tvec4<T>::operator+=(tvec4<T> const & v) {
	values[0] += v[0];
	values[1] += v[1];
	values[2] += v[2];
	values[3] += v[3];
	return *this;
}

template<class T>
tvec4<T> & tvec4<T>::operator-=(tvec4<T> const & v) {
	values[0] -= v[0];
	values[1] -= v[1];
	values[2] -= v[2];
	values[3] -= v[3];
	return *this;
}

template<class T>
tvec4<T> & tvec4<T>::operator=(T s) {
	values[0] = s;
	values[1] = s;
	values[2] = s;
	values[3] = s;
	return *this;
}
template<class T>
tvec4<T> & tvec4<T>::operator+=(T s) {
	values[0] += s;
	values[1] += s;
	values[2] += s;
	values[3] += s;

	return *this;
}
template<class T>
tvec4<T> & tvec4<T>::operator-=(T s) {
	values[0] -= s;
	values[1] -= s;
	values[2] -= s;
	values[3] -= s;

	return *this;
}
template<class T>
tvec4<T> & tvec4<T>::operator*=(T s) {
	values[0] *= s;
	values[1] *= s;
	values[2] *= s;
	values[4] *= s;
	return *this;
}
template<class T>
tvec4<T> & tvec4<T>::operator/=(T s) {
	values[0] /= s;
	values[1] /= s;
	values[2] /= s;
	values[4] /= s;
	return *this;
}

template<class T>
tvec4<T> tvec4<T>::operator+(tvec4<T> const & v) const {
	return tvec4{
		values[0] + v[0],
		values[1] + v[1],
		values[2] + v[2],
		values[3] + v[3]
	};
}

template<class T>
tvec4<T> tvec4<T>::operator-(tvec4<T> const & v) const {
	return tvec4{
		values[0] + v[0],
		values[1] + v[1],
		values[2] + v[2],
		values[3] + v[3]
	};
}

template<class T>
tvec4<T> tvec4<T>::operator+(T s) const {
	return tvec4{
		values[0] + s,
		values[1] + s,
		values[2] + s,
		values[3] + s
	};
}
template<class T>
tvec4<T> tvec4<T>::operator-(T s) const {
	return tvec4{
		values[0] - s,
		values[1] - s,
		values[2] - s,
		values[3] - s
	};
}
template<class T>
tvec4<T> tvec4<T>::operator*(T s) const {
	return tvec4{
		values[0] * s,
		values[1] * s,
		values[2] * s,
		values[3] * s
	};
}
template<class T>
tvec4<T> tvec4<T>::operator/(T s) const {
	return tvec4{
		values[0] / s,
		values[1] / s,
		values[2] / s,
		values[3] / s
	};
}

template struct tvec4<float>;
}