#include <cstring>

namespace lm {

template<typename T>
bool tmat4<T>::operator==(tmat4<T> const & m) const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (arr[i][j] != m.arr[i][j])
				return false;
		}
	}
	return true;
}

template<typename T>
tvec4<T>& tmat4<T>::operator[](int i) {
	return values[i];
}

template<typename T>
tvec4<T> const & tmat4<T>::operator[](int i) const {
	return values[i];
}

template<typename T>
tmat4<T> tmat4<T>::operator=(tmat4<T> const & m) {
	memcpy(&values, &m.values, 16 * sizeof(T));
	return *this;
}

template<typename T>
tmat4<T> tmat4<T>::operator+(tmat4<T> const & m) const {
	tmat4<T> res;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			res[i][j] = arr[i][j] + m.arr[i][j];
	return res;
}

template<typename T>
tmat4<T> tmat4<T>::operator-(tmat4<T> const & m) const {
	tmat4<T> res;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			res[i][j] = arr[i][j] - m.arr[i][j];
	return res;
}

template<typename T>
tmat4<T> tmat4<T>::operator*(tmat4<T> const & m) const {
	tmat4<T> res;
	int k, r, c;
	for (c = 0; c < 4; ++c)
		for (r = 0; r < 4; ++r) {
			res[c][r] = 0.0f;
			for (k = 0; k < 4; ++k)
				res[c][r] += arr[k][r] * m[c][k];
		}
	return res;
}

template<typename T>
tmat4<T> tmat4<T>::operator*(T s) const {
	tmat4<T> res;
	res.values[0] = values[0] * s;
	res.values[0] = values[1] * s;
	res.values[0] = values[2] * s;
	res.values[0] = values[3] * s;
	return res;
}

template<typename T>
tvec4<T> tmat4<T>::operator*(tvec4<T> const & v) const {
	tvec4<T> r;
	for (int j = 0; j < 4; ++j) {
		r[j] = 0.f;
		for (int i = 0; i < 4; ++i)
			r[j] += arr[i][j] * v[i];
	}
	return r;
}

template<typename T>
tmat4<T> & tmat4<T>::operator+=(tmat4<T> const & m) {
	*this = *this + m;
	return *this;
}

template<typename T>
tmat4<T> & tmat4<T>::operator-=(tmat4<T> const & m) {
	*this = *this - m;
	return *this;
}

template<typename T>
tmat4<T> & tmat4<T>::operator*=(tmat4<T> const & m) {
	*this = *this * m;
	return *this;
}

template<typename T>
tmat4<T> & tmat4<T>::operator*=(T scalar) {
	*this = *this * scalar;
	return *this;
}

}