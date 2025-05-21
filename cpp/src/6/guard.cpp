#include "guard.hpp"
#include "map.hpp"




#include <iostream>
namespace aoc {

Guard::Guard(Map& map) : m_map{map} {}

Guard& Guard::set_position(uVector2 new_position) noexcept {
	m_position = new_position;
	if (!is_out()) {
		auto [it, e] = m_map.visited.insert({new_position, {}});
		stuck_in_loop = it->second.test(static_cast<u8>(m_facing));
		it->second.set(static_cast<u8>(m_facing));
		//if (stuck_in_loop) std::cout << it->second << " " << m_position.x << " " << m_position.y << std::endl;
	}
	return *this;
}

Guard& Guard::set_main_position(uVector2 new_position) noexcept {
	m_main_position = new_position;
	return *this;
}

Guard& Guard::set_main_facing(Facing new_facing) noexcept {
	m_main_facing = new_facing;
	return *this;
}


void Guard::reset() noexcept {
	set_position(m_main_position);
	set_facing(m_main_facing);
	stuck_in_loop = false;
}

Guard& Guard::set_facing(Facing new_facing) noexcept {
	m_facing = new_facing;
	switch (m_facing) {
	case Facing::Up:    m_facing_vec = { 0,-1}; break;
	case Facing::Right: m_facing_vec = { 1, 0}; break;
	case Facing::Down:  m_facing_vec = { 0, 1}; break;
	case Facing::Left:  m_facing_vec = {-1, 0}; break;
	default: __builtin_unreachable();
	}
	return *this;
}

uVector2 Guard::get_position() const noexcept {
	return m_position;
}

bool Guard::is_out() const noexcept {
	return m_position.x >= m_map.size.x || m_position.y >= m_map.size.y;
}

void Guard::turn_right() noexcept {
	set_facing(static_cast<Facing>((static_cast<int>(m_facing)+1) % 4));
}

void Guard::advance() noexcept {
	auto next_position = m_position + m_facing_vec;
	
	if (m_map.check_collision(next_position)) {
		turn_right();
		advance();
		return;
	}

	set_position(next_position);
}

}
