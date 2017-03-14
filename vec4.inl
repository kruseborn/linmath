namespace lm {
template<typename T>
T& tvec4<T>::operator[](int i) {
	return values[i];
}

template<typename T>
T const & tvec4<T>::operator[](int i) const {
	return values[i];
}

template<typename T>
bool tvec4<T>::operator==(tvec4<T> const & v) const {
	return
		values[0] == v[0] &&
		values[1] == v[1] &&
		values[2] == v[2] &&
		values[3] == v[3];
}

template<typename T>
tvec4<T> & tvec4<T>::operator=(tvec4<T> const & v) {
	values[0] = v[0];
	values[1] = v[1];
	values[2] = v[2];
	values[3] = v[3];
	return *this;
}

template<typename T>
tvec4<T> & tvec4<T>::operator+=(tvec4<T> const & v) {
	values[0] += v[0];
	values[1] += v[1];
	values[2] += v[2];
	values[3] += v[3];
	return *this;
}

template<typename T>
tvec4<T> & tvec4<T>::operator-=(tvec4<T> const & v) {
	values[0] -= v[0];
	values[1] -= v[1];
	values[2] -= v[2];
	values[3] -= v[3];
	return *this;
}

template<typename T>
tvec4<T> & tvec4<T>::operator=(T s) {
	values[0] = s;
	values[1] = s;
	values[2] = s;
	values[3] = s;
	return *this;
}

template<typename T>
tvec4<T> & tvec4<T>::operator+=(T s) {
	values[0] += s;
	values[1] += s;
	values[2] += s;
	values[3] += s;

	return *this;
}

template<typename T>
tvec4<T> & tvec4<T>::operator-=(T s) {
	values[0] -= s;
	values[1] -= s;
	values[2] -= s;
	values[3] -= s;

	return *this;
}

template<typename T>
tvec4<T> & tvec4<T>::operator*=(T s) {
	values[0] *= s;
	values[1] *= s;
	values[2] *= s;
	values[3] *= s;
	return *this;
}

template<typename T>
tvec4<T> & tvec4<T>::operator/=(T s) {
	values[0] /= s;
	values[1] /= s;
	values[2] /= s;
	values[3] /= s;
	return *this;
}

template<typename T>
tvec4<T> tvec4<T>::operator+(tvec4<T> const & v) const {
	return tvec4<T>{
		values[0] + v[0],
		values[1] + v[1],
		values[2] + v[2],
		values[3] + v[3]
	};
}

template<typename T>
tvec4<T> tvec4<T>::operator-(tvec4<T> const & v) const {
	return tvec4<T>{
		values[0] - v[0],
		values[1] - v[1],
		values[2] - v[2],
		values[3] - v[3]
	};
}

template<typename T>
tvec4<T> tvec4<T>::operator+(T s) const {
	return tvec4<T>{
		values[0] + s,
		values[1] + s,
		values[2] + s,
		values[3] + s
	};
}

template<typename T>
tvec4<T> tvec4<T>::operator-(T s) const {
	return tvec4<T>{
		values[0] - s,
		values[1] - s,
		values[2] - s,
		values[3] - s
	};
}

template<typename T>
tvec4<T> tvec4<T>::operator*(T s) const {
	return tvec4<T>{
		values[0] * s,
		values[1] * s,
		values[2] * s,
		values[3] * s
	};
}

template<typename T>
tvec4<T> tvec4<T>::operator/(T s) const {
	return tvec4<T>{
		values[0] / s,
		values[1] / s,
		values[2] / s,
		values[3] / s
	};
}
}
