namespace lm {

template<typename T>
T& tvec3<T>::operator[](int i) {
	return values[i];
}

template<typename T>
T const & tvec3<T>::operator[](int i) const {
	return values[i];
}

template<typename T>
bool tvec3<T>::operator==(tvec3<T> const & v) const {
	return
		values[0] == v[0] &&
		values[1] == v[1] &&
		values[2] == v[2];
}

template<typename T>
tvec3<T> & tvec3<T>::operator=(tvec3<T> const & v) {
	values[0] = v[0];
	values[1] = v[1];
	values[2] = v[2];
	return *this;
}

template<typename T>
tvec3<T> & tvec3<T>::operator+=(tvec3<T> const & v) {
	values[0] += v[0];
	values[1] += v[1];
	values[2] += v[2];
	return *this;
}

template<typename T>
tvec3<T> & tvec3<T>::operator-=(tvec3<T> const & v) {
	values[0] -= v[0];
	values[1] -= v[1];
	values[2] -= v[2];
	return *this;
}

//scalar

template<typename T>
tvec3<T> & tvec3<T>::operator=(T s) {
	values[0] = s;
	values[1] = s;
	values[2] = s;
	return *this;
}

template<typename T>
tvec3<T> & tvec3<T>::operator+=(T s) {
	values[0] += s;
	values[1] += s;
	values[2] += s;
	return *this;
}

template<typename T>
tvec3<T> & tvec3<T>::operator-=(T s) {
	values[0] -= s;
	values[1] -= s;
	values[2] -= s;
	return *this;
}

template<typename T>
tvec3<T> & tvec3<T>::operator*=(T s) {
	values[0] *= s;
	values[1] *= s;
	values[2] *= s;
	return *this;
}

template<typename T>
tvec3<T> & tvec3<T>::operator/=(T s) {
	values[0] /= s;
	values[1] /= s;
	values[2] /= s;
	return *this;
}

template<typename T>
tvec3<T> tvec3<T>::operator+(tvec3<T> const & v) const {
	return tvec3<T>{
		values[0] + v[0],
		values[1] + v[1],
		values[2] + v[2]
	};
}

template<typename T>
tvec3<T> tvec3<T>::operator-(tvec3<T> const & v) const {
	return tvec3<T>{
		values[0] - v[0],
		values[1] - v[1],
		values[2] - v[2]
	};
}

template<typename T>
tvec3<T> tvec3<T>::operator+(T s) const {
	return tvec3<T>{
		values[0] + s,
		values[1] + s,
		values[2] + s
	};
}

template<typename T>
tvec3<T> tvec3<T>::operator-(T s) const {
	return tvec3<T>{
		values[0] - s,
		values[1] - s,
		values[2] - s
	};
}

template<typename T>
tvec3<T> tvec3<T>::operator*(T s) const {
	return tvec3<T>{
		values[0] * s,
		values[1] * s,
		values[2] * s
	};
}

template<typename T>
tvec3<T> tvec3<T>::operator/(T s) const {
	return tvec3<T>{
		values[0] / s,
		values[1] / s,
		values[2] / s,
	};
}
}