#include "utils.hpp"
#include "ints.hpp"
#include "vector2.hpp"
#include "map.hpp"

int main() {
	utils::cd_app_workdir();
	aoc::Map map(utils::read_whole_file("inputs/6.txt"));

	map.run();
	
	return 0;
}
