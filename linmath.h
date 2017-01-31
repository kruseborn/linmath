#pragma once

namespace lm {
	template<class T> struct tvec2 {
		T & operator[](int i);
		T const & operator[](int i) const;
		bool operator==(tvec2<T> const & v) const;

		tvec2<T> operator+(tvec2<T> const & v) const;
		tvec2<T> operator-(tvec2<T> const & v) const;

		tvec2<T> operator+(T scalar) const;
		tvec2<T> operator-(T scalar) const;
		tvec2<T> operator*(T scalar) const;
		tvec2<T> operator/(T scalar) const;


		tvec2<T> & operator=(tvec2<T> const & v);
		tvec2<T> & operator+=(tvec2<T> const & v);
		tvec2<T> & operator-=(tvec2<T> const & v);

		tvec2<T> & operator=(T scalar);
		tvec2<T> & operator+=(T scalar);
		tvec2<T> & operator-=(T scalar);
		tvec2<T> & operator*=(T scalar);
		tvec2<T> & operator/=(T scalar);


		union {
			struct { T x, y; };
			struct { T r, g; };
			struct { T s, t; };
			T values[2];
		};
	};

	template<class T> struct tvec3 {
		T & operator[](int i);
		T const & operator[](int i) const;
		bool operator==(tvec3<T> const & v) const;


		tvec3<T> operator+(tvec3<T> const & v) const;
		tvec3<T> operator-(tvec3<T> const & v) const;

		tvec3<T> operator+(T scalar) const;
		tvec3<T> operator-(T scalar) const;
		tvec3<T> operator*(T scalar) const;
		tvec3<T> operator/(T scalar) const;


		tvec3<T> & operator=(tvec3<T> const & v);
		tvec3<T> & operator+=(tvec3<T> const & v);
		tvec3<T> & operator-=(tvec3<T> const & v);

		tvec3<T> & operator=(T scalar);
		tvec3<T> & operator+=(T scalar);
		tvec3<T> & operator-=(T scalar);
		tvec3<T> & operator*=(T scalar);
		tvec3<T> & operator/=(T scalar);

		union {
			struct { T x, y, z; };
			struct { T r, g, b; };
			struct { T s, t, p; };
			T values[3];
		};
	};

	template<class T> struct tvec4 {
		T & operator[](int i);
		T const & operator[](int i) const;

		bool operator==(tvec4<T> const & v) const;

		tvec4<T> operator+(tvec4<T> const & v) const;
		tvec4<T> operator-(tvec4<T> const & v) const;

		tvec4<T> operator+(T scalar) const;
		tvec4<T> operator-(T scalar) const;
		tvec4<T> operator*(T scalar) const;
		tvec4<T> operator/(T scalar) const;

		tvec4<T> & operator=(tvec4<T> const & v);
		tvec4<T> & operator+=(tvec4<T> const & v);
		tvec4<T> & operator-=(tvec4<T> const & v);

		tvec4<T> & operator=(T scalar);
		tvec4<T> & operator+=(T scalar);
		tvec4<T> & operator-=(T scalar);
		tvec4<T> & operator*=(T scalar);
		tvec4<T> & operator/=(T scalar);

		union {
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			struct { T s, t, p, q; };
			T values[4];
		};
	};

	template<class T> struct tmat4 {
		tvec4<T> & operator[](int i);
		tvec4<T> const & operator[](int i) const;
		bool operator==(tmat4<T> const & m) const;

		tmat4<T> operator=(tmat4<T> const & m);
		tmat4<T> operator+(tmat4<T> const & m) const;
		tmat4<T> operator-(tmat4<T> const & m) const;
		tmat4<T> operator*(tmat4<T> const & m) const;

		tmat4<T> operator*(T scalar) const;
		tvec4<T> operator*(tvec4<T> const & v) const;

		tmat4<T> & operator+=(tmat4<T> const & m);
		tmat4<T> & operator-=(tmat4<T> const & m);
		tmat4<T> & operator*=(tmat4<T> const & m);

		tmat4<T> & operator*=(T scalar);

		union {
			tvec4<T> values[4];
			T arr[4][4];
		};
	};

	extern template struct tmat4<float>;
	extern template struct tvec4<float>;
	extern template struct tvec3<float>;
	extern template struct tvec2<float>;

	using mat4 = tmat4<float>;
	using vec4 = tvec4<float>;
	using vec3 = tvec3<float>;
	using vec2 = tvec2<float>;

}