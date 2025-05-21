#ifndef AOC_VECTOR2_HPP
#define AOC_VECTOR2_HPP

// Vector2 by retrodeb
#include "ints.hpp"
#include <type_traits>
#include <bitset>

template<typename VType>
requires std::is_arithmetic_v<VType>
struct Vector2 {
	VType x, y;

	using type = VType;

	template<typename T>
	constexpr Vector2& operator+=(Vector2<T> const& v) noexcept {
		x += v.x;
		y += v.y;
		return *this;
	}

	template<typename T>
	constexpr Vector2 operator+(Vector2<T> const& v) const noexcept {
		Vector2 vec = *this;
		return vec += v;
	}

	template<typename T>
	constexpr Vector2& operator-=(Vector2<T> const& v) noexcept {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	template<typename T>
	constexpr Vector2 operator-(Vector2<T> const& v) const noexcept {
		Vector2 vec {*this};
		return vec -= v;
	}

	template<typename T>
	constexpr Vector2& operator*=(Vector2<T> const& v) noexcept {
		x *= v.x;
		y *= v.y;
		return *this;
	}

	template<typename T>
	constexpr Vector2 operator*(Vector2<T> const& v) const noexcept {
		Vector2 vec {*this};
		return vec *= v;
	}

	template<typename T>
	constexpr Vector2& operator/=(Vector2<T> const& v) noexcept {
		x /= v.x;
		y /= v.y;
		return *this;
	}

	template<typename T>
	constexpr Vector2 operator/(Vector2<T> const& v) const noexcept {
		Vector2 vec {*this};
		return vec /= v;
	}

	template<typename T>
	constexpr bool operator==(Vector2<T> const& v) const noexcept {
		return v.x == x && v.y == y;
	}

	template<typename T>
	constexpr bool operator!=(Vector2<T> const& v) const noexcept {
		return !operator==(v);
	}
};

using fVector2 = Vector2<float>;
using iVector2 = Vector2<i32>;
using uVector2 = Vector2<u32>;

namespace std {
	template <>
	struct hash<uVector2> {
		std::size_t operator()(uVector2 const& v) const {
			return (static_cast<std::size_t>(v.x) << sizeof(u32)*8) | v.y;
		}
	};
}

#endif
