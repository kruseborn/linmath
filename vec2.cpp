#include "linmath.h"

namespace lm {
template<class T>
T& tvec2<T>::operator[](int i) {
	return values[i];
}

template<class T>
T const & tvec2<T>::operator[](int i) const {
	return values[i];
}

template<class T>
bool tvec2<T>::operator==(tvec2<T> const & v) const {
	return
		values[0] == v[0] &&
		values[1] == v[1];
}
template<class T>
tvec2<T> & tvec2<T>::operator=(tvec2<T> const & v) {
	values[0] = v[0];
	values[1] = v[1];
	return *this;
}

template<class T>
tvec2<T> & tvec2<T>::operator+=(tvec2<T> const & v) {
	values[0] += v[0];
	values[1] += v[1];
	return *this;
}

template<class T>
tvec2<T> & tvec2<T>::operator-=(tvec2<T> const & v) {
	values[0] -= v[0];
	values[1] -= v[1];
	return *this;
}


//scalar
template<class T>
tvec2<T> & tvec2<T>::operator=(T s) {
	values[0] = s;
	values[1] = s;
	return *this;
}
template<class T>
tvec2<T> & tvec2<T>::operator+=(T s) {
	values[0] += s;
	values[1] += s;
	return *this;
}
template<class T>
tvec2<T> & tvec2<T>::operator-=(T s) {
	values[0] -= s;
	values[1] -= s;
	return *this;
}
template<class T>
tvec2<T> & tvec2<T>::operator*=(T s) {
	values[0] *= s;
	values[1] *= s;
	return *this;
}
template<class T>
tvec2<T> & tvec2<T>::operator/=(T s) {
	values[0] /= s;
	values[1] /= s;
	return *this;
}
template<class T>
tvec2<T> tvec2<T>::operator+(tvec2<T> const & v) const {
	return tvec2{
		values[0] + v[0],
		values[1] + v[1]
	};
}

template<class T>
tvec2<T> tvec2<T>::operator-(tvec2<T> const & v) const {
	return tvec2{
		values[0] + v[0],
		values[1] + v[1]
	};
}

template<class T>
tvec2<T> tvec2<T>::operator+(T s) const {
	return tvec2{
		values[0] + s,
		values[1] + s
	};
}
template<class T>
tvec2<T> tvec2<T>::operator-(T s) const {
	return tvec2{
		values[0] - s,
		values[1] - s
	};
}
template<class T>
tvec2<T> tvec2<T>::operator*(T s) const {
	return tvec2{
		values[0] * s,
		values[1] * s
	};
}
template<class T>
tvec2<T> tvec2<T>::operator/(T s) const {
	return tvec2{
		values[0] / s,
		values[1] / s,
		values[2] / s,
	};
}

template struct tvec2<float>;
}