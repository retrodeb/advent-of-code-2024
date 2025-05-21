#include "utils.hpp"
#include "vector2.hpp"

#include <iostream>
#include <ranges>
#include <algorithm>
#include <utility>

namespace aoc {

struct Context {
	std::string input;
	u32 width, height;
};

struct Map {
	uVector2 size;
	
	Map(std::string input) : m_chars(std::move(input)) {
		size.x = m_chars.find('\n');
		size.y = std::ranges::count(m_chars, '\n');
		
		for (auto line : m_chars | std::views::split('\n') | std::views::take(size.y-1)) {
			if (line.size() != size.x) {
				std::cerr << "Input line width must be: " << size.x << std::endl;
				std::abort();
			}
		}
	}

	char get_char(uVector2 pos) const {
		return m_chars.at(pos.y * (size.x+1) + pos.x);
	}

	bool check_match(std::string_view xmas, uVector2 pos, Vector2<i8> add) const {
		Vector2<u32> last(
			pos.x + (static_cast<i32>(xmas.size())-1) * add.x,
			pos.y + (static_cast<i32>(xmas.size())-1) * add.y
		);
		
		if ((pos.x >= size.x) ||
			(pos.y >= size.y) ||
			(last.x >= size.x) ||
			(last.y >= size.y)
		) return false;
		
		for (u32 i=0; i<xmas.size(); i++) {
			if (xmas[i] != get_char(pos)) return false;
			pos += add;
		}
		return true;
	}

	
private:
	std::string m_chars;
};


void part_one(Map const& map) {
	std::string_view xmas = "XMAS";
	u32 xmas_count {};

	for (u32 y{}; y<map.size.y; ++y) {
		for (u32 x{}; x<map.size.x; ++x) {
			uVector2 pos {x, y};
			if (map.check_match(xmas, pos, { 1,  0})) ++xmas_count;
			if (map.check_match(xmas, pos, {-1,  0})) ++xmas_count;
			if (map.check_match(xmas, pos, { 0,  1})) ++xmas_count;
			if (map.check_match(xmas, pos, { 0, -1})) ++xmas_count;
			if (map.check_match(xmas, pos, { 1,  1})) ++xmas_count;
			if (map.check_match(xmas, pos, { 1, -1})) ++xmas_count;
			if (map.check_match(xmas, pos, {-1,  1})) ++xmas_count;
			if (map.check_match(xmas, pos, {-1, -1})) ++xmas_count;
		}
	}

	std::cout << "XMAS count: " << xmas_count << " (part one)" << std::endl;
}

void part_two(Map const& map) {
	u32 xmas_count {};
	std::string_view xmas = "MAS";

	for (u32 y{}; y<map.size.y; ++y) {
		for (u32 x{}; x<map.size.x; ++x) {
			if (
				(map.check_match(xmas, {x-1, y-1}, {1, 1}) || map.check_match(xmas, {x+1, y+1}, {-1, -1})) &&
				(map.check_match(xmas, {x-1, y+1}, {1, -1}) || map.check_match(xmas, {x+1, y-1}, {-1, 1}))
			) ++xmas_count;
		}
	}
	std::cout << "XMAS count: " << xmas_count << " (part two)" << std::endl;
}

}

int main() {
	utils::cd_app_workdir();
	aoc::Map map(utils::read_whole_file("inputs/4.txt"));
	aoc::part_one(map);
	aoc::part_two(map);
	return 0;
}
