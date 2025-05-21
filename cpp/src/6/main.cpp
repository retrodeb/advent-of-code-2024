#include "utils.hpp"
#include "ints.hpp"
#include "vector2.hpp"
#include "map.hpp"
#include <iostream>

namespace aoc {

void part_one(Map& map) {
	map.run();
	std::cout << "Total guard visits: " << map.visited.size() << std::endl;
}

void part_two(Map& map) {
	auto possible_obstructions {std::move(map.visited)};
	
	// Part two
	u32 total_obstructions {};
	for (auto [position, _] : possible_obstructions) {
		map.guard.reset();
		map.visited.clear();
		Block& block = map.get_block(position);
		block.type = Block::Type::Obstacle;
		map.run();
		block.type = Block::Type::Empty;
		if (map.guard.stuck_in_loop) ++total_obstructions;
	}

	std::cout << "Total possible obstructions: " << total_obstructions << std::endl;
}

}

int main() {
	utils::cd_app_workdir();
	aoc::Map map(utils::read_whole_file("inputs/6.txt"));
	aoc::part_one(map);
	aoc::part_two(map);
	return 0;
}
