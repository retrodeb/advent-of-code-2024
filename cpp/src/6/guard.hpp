#ifndef AOC_GUARD_HPP
#define AOC_GUARD_HPP

#include "vector2.hpp"

namespace aoc {

struct Map;

struct Guard {
	enum class Facing {
		Up,
		Right,
		Down,
		Left
	};

	bool stuck_in_loop {};
	Guard(Map& map);

	Guard& set_facing(Facing new_facing) noexcept;
	Guard& set_position(uVector2 new_position) noexcept;
	Guard& set_main_facing(Facing facing) noexcept;
	Guard& set_main_position(uVector2 new_position) noexcept;
	[[nodiscard]] uVector2 get_position() const noexcept;

	void reset() noexcept;
	bool is_out() const noexcept;
	
	void turn_right() noexcept;
	void advance() noexcept;

private:
	Facing m_facing {};
	uVector2 m_position;
	uVector2 m_main_position;
	Facing m_main_facing;
	Vector2<i8> m_facing_vec;
	Map& m_map;
};

}

#endif
