#ifndef AOC_MAP_HPP
#define AOC_MAP_HPP

#include "block.hpp"
#include "guard.hpp"
#include "vector2.hpp"

#include <set>
#include <string>
#include <vector>
#include <unordered_map>
#include <bitset>

namespace aoc {

struct Map {
	explicit Map(std::string const& map_str);
	Map(Map&&) = delete;
	Map(Map&) = delete;

	Block& get_block(uVector2 position) noexcept;
	Block const& get_block(uVector2 position) const noexcept;
	
	bool check_collision(uVector2 position) const noexcept;

	void run();

	std::unordered_map<uVector2, std::bitset<4>> visited;
	std::vector<Block> blocks;
	Guard guard;
	uVector2 size;
};

}

#endif
