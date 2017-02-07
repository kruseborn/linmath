//#include "linmath.h"
namespace lm {

template<typename T>
T& tvec2<T>::operator[](int i) {
	return values[i];
}


template<typename T>
T const & tvec2<T>::operator[](int i) const {
	return values[i];
}


template<typename T>
bool tvec2<T>::operator==(tvec2<T> const & v) const {
	return
		values[0] == v[0] &&
		values[1] == v[1];
}

template<typename T>
tvec2<T> & tvec2<T>::operator=(tvec2<T> const & v) {
	values[0] = v[0];
	values[1] = v[1];
	return *this;
}

template<typename T>
tvec2<T> & tvec2<T>::operator+=(tvec2<T> const & v) {
	values[0] += v[0];
	values[1] += v[1];
	return *this;
}

template<typename T>
tvec2<T> & tvec2<T>::operator-=(tvec2<T> const & v) {
	values[0] -= v[0];
	values[1] -= v[1];
	return *this;
}


//scalar

template<typename T>
tvec2<T> & tvec2<T>::operator=(T s) {
	values[0] = s;
	values[1] = s;
	return *this;
}

template<typename T>
tvec2<T> & tvec2<T>::operator+=(T s) {
	values[0] += s;
	values[1] += s;
	return *this;
}

template<typename T>
tvec2<T> & tvec2<T>::operator-=(T s) {
	values[0] -= s;
	values[1] -= s;
	return *this;
}

template<typename T>
tvec2<T> & tvec2<T>::operator*=(T s) {
	values[0] *= s;
	values[1] *= s;
	return *this;
}

template<typename T>
tvec2<T> & tvec2<T>::operator/=(T s) {
	values[0] /= s;
	values[1] /= s;
	return *this;
}

template<typename T>
tvec2<T> tvec2<T>::operator+(tvec2<T> const & v) const {
	return tvec2<T>{
		values[0] + v[0],
		values[1] + v[1]
	};
}

template<typename T>
tvec2<T> tvec2<T>::operator-(tvec2<T> const & v) const {
	return tvec2<T>{
		values[0] - v[0],
		values[1] - v[1]
	};
}

template<typename T>
tvec2<T> tvec2<T>::operator+(T s) const {
	return tvec2<T>{
		values[0] + s,
		values[1] + s
	};
}

template<typename T>
tvec2<T> tvec2<T>::operator-(T s) const {
	return tvec2<T>{
		values[0] - s,
		values[1] - s
	};
}

template<typename T>
tvec2<T> tvec2<T>::operator*(T s) const {
	return tvec2<T>{
		values[0] * s,
		values[1] * s
	};
}

template<typename T>
tvec2<T> tvec2<T>::operator/(T s) const {
	return tvec2<T>{
		values[0] / s,
		values[1] / s,
	};
}

}