#include "map.hpp"

#include <iostream>
#include <algorithm>
#include <cassert>

namespace aoc {

Map::Map(std::string const& map_str) : guard {*this} {
	// Parse map
	size.x = map_str.find('\n');
	size.y = std::ranges::count(map_str, '\n');

	if (map_str.size() != ((size.x+1) * size.y)) {
		std::cerr << "Invalid map size, (" << size.x << "x" << size.y << "), string size: " << map_str.size() << " missing blocks?" << std::endl;
		std::abort();
	}
	
	blocks.reserve(size.x * size.y);

	for (Vector2<u32> coord {}; coord.y < size.y; ++coord.x) {
		switch (char ch = map_str[coord.y*(size.x+1) + coord.x]) {
		case '^':
			guard.set_main_facing(Guard::Facing::Up);
			goto assign;
		case 'v':
			guard.set_main_facing(Guard::Facing::Down);
			goto assign;
		case '>':
			guard.set_main_facing(Guard::Facing::Right);
			goto assign;
		case '<':
			guard.set_main_facing(Guard::Facing::Left);
		assign:
			guard.set_main_position(coord);
			guard.reset(); // Set main position
			blocks.emplace_back(Block::Type::Empty);
			break;
				
		case '.':
			blocks.emplace_back(Block::Type::Empty);
			break;
		case '#':
			blocks.emplace_back(Block::Type::Obstacle);
			break;
		case '\n':
			coord.y++;
			coord.x = -1;
			break;
		default:
			std::cerr << "Invalid block '" << ch << "'" << std::endl;
			std::abort();
		}
	}
}

Block& Map::get_block(uVector2 position) noexcept {
	return const_cast<Block&>(const_cast<Map const&>(*this).get_block(position));
}

Block const& Map::get_block(uVector2 position) const noexcept {
	assert(position.x < size.x && position.y < size.y);
	return blocks[position.x + position.y * size.x];
}

bool Map::check_collision(uVector2 position) const noexcept {
	if (position.x >= size.x || position.y >= size.y) return false; // Out of map
	return get_block(position).type == Block::Type::Obstacle;
}

void Map::run() {

	// Part one
	while (!guard.is_out()) {
		guard.advance();
	}

	std::cout << "Total guard visits: " << visited.size() << std::endl;

	auto possible_obstructions {std::move(visited)};
	visited.clear();
	
	// Part two
	u32 total_obstructions {};
	for (auto [position, _] : possible_obstructions) {
		guard.reset();
		visited.clear();
		get_block(position).type = Block::Type::Obstacle;
		while (!guard.is_out() && !guard.stuck_in_loop) {
			guard.advance();
		}
		get_block(position).type = Block::Type::Empty;
		if (guard.stuck_in_loop) ++total_obstructions;
	}

	std::cout << "Total possible obstructions: " << total_obstructions << std::endl;
}

}
