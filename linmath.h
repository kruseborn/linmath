#pragma once

#include <cstdint>

namespace lm {
	template<typename T>
	struct tvec2 {
		T & operator[](int i);
		T const & operator[](int i) const;
		bool operator==(tvec2 const & v) const;

		tvec2 operator+(tvec2 const & v) const;
		tvec2 operator-(tvec2 const & v) const;

		tvec2 operator+(T scalar) const;
		tvec2 operator-(T scalar) const;
		tvec2 operator*(T scalar) const;
		tvec2 operator/(T scalar) const;

		tvec2 & operator=(tvec2 const & v);
		tvec2 & operator+=(tvec2 const & v);
		tvec2 & operator-=(tvec2 const & v);

		tvec2 & operator=(T scalar);
		tvec2 & operator+=(T scalar);
		tvec2 & operator-=(T scalar);
		tvec2 & operator*=(T scalar);
		tvec2 & operator/=(T scalar);

		union {
			struct { T x, y; };
			struct { T r, g; };
			T values[2];
		};
	};
	template<typename T>
	struct tvec3 {
		T & operator[](int i);
		T const & operator[](int i) const;
		bool operator==(tvec3 const & v) const;


		tvec3 operator+(tvec3 const & v) const;
		tvec3 operator-(tvec3 const & v) const;

		tvec3 operator+(T scalar) const;
		tvec3 operator-(T scalar) const;
		tvec3 operator*(T scalar) const;
		tvec3 operator/(T scalar) const;


		tvec3 & operator=(tvec3 const & v);
		tvec3 & operator+=(tvec3 const & v);
		tvec3 & operator-=(tvec3 const & v);

		tvec3 & operator=(T scalar);
		tvec3 & operator+=(T scalar);
		tvec3 & operator-=(T scalar);
		tvec3 & operator*=(T scalar);
		tvec3 & operator/=(T scalar);

		union {
			struct { T x, y, z; };
			struct { T r, g, b; };
			T values[3];
		};
	};
	template<typename T>
	struct tvec4 {
		T & operator[](int i);
		T const & operator[](int i) const;

		bool operator==(tvec4 const & v) const;

		tvec4 operator+(tvec4 const & v) const;
		tvec4 operator-(tvec4 const & v) const;

		tvec4 operator+(T scalar) const;
		tvec4 operator-(T scalar) const;
		tvec4 operator*(T scalar) const;
		tvec4 operator/(T scalar) const;

		tvec4 & operator=(tvec4 const & v);
		tvec4 & operator+=(tvec4 const & v);
		tvec4 & operator-=(tvec4 const & v);

		tvec4 & operator=(T scalar);
		tvec4 & operator+=(T scalar);
		tvec4 & operator-=(T scalar);
		tvec4 & operator*=(T scalar);
		tvec4 & operator/=(T scalar);

		union {
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			T values[4];
		};
	};

	template<typename T>
	struct tmat4 {
		tvec4<T> & operator[](int i);
		tvec4<T> const & operator[](int i) const;
		bool operator==(tmat4<T> const & m) const;

		tmat4 operator=(tmat4 const & m);
		tmat4 operator+(tmat4 const & m) const;
		tmat4 operator-(tmat4 const & m) const;
		tmat4 operator*(tmat4 const & m) const;

		tmat4 operator*(T scalar) const;
		tvec4<T> operator*(tvec4<T> const & v) const;

		tmat4 & operator+=(tmat4 const & m);
		tmat4 & operator-=(tmat4 const & m);
		tmat4 & operator*=(tmat4 const & m);

		tmat4 & operator*=(T scalar);

		union {
			tvec4<T> values[4];
			T arr[4][4];
		};
	};

	template<typename T>
	struct tquat {
		bool operator==(tquat const & q) const;
		tquat & operator=(tquat const & q);
		
		tquat operator+(tquat const & q) const;
		tquat operator-(tquat const & q) const;
		tquat operator*(tquat const & q) const;
		tvec3<T> operator*(tvec3<T> const & v) const;

		tquat & operator+=(tquat const & q);
		tquat & operator-=(tquat const & q);
		tquat & operator*=(tquat const & q);

		T x, y, z, w;
	};

	using mat4 = tmat4<float>;
	using vec4 = tvec4<float>;
	using vec3 = tvec3<float>;
	using vec2 = tvec2<float>;
	using quat = tquat<float>;

	using ivec3 = tvec3<uint32_t>;
}
extern template struct lm::tmat4<float>;
extern template struct lm::tvec4<float>;
extern template struct lm::tvec3<float>;
extern template struct lm::tvec2<float>;
extern template struct lm::tquat<float>;

#include "vec4.inl"
#include "vec3.inl"
#include "vec2.inl"
#include "mat4.inl"
#include "quat.inl"
