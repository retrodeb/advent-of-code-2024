#include "utils.hpp"

#include <regex>
#include <iostream>

namespace aoc {

void part_one(std::string const& input) {
	std::regex pattern(R"(mul\((\d+),(\d+)\))");
	auto mul_begin = std::sregex_iterator(input.cbegin(), input.cend(), pattern);
	auto mul_end = std::sregex_iterator();

	i64 result {};
	for (auto it = mul_begin; it != mul_end; ++it) {
		auto& matches = *it;
		result += std::stoi(matches[1]) * std::stoi(matches[2]);
	}
	std::cout << "Result: " << result << " (part one)" << std::endl;
}

void part_two(std::string const& input) {
	std::regex pattern(R"(mul\((\d+),(\d+)\)|(do\(\)|don\'t\(\)))");
	auto mul_begin = std::sregex_iterator(input.cbegin(), input.cend(), pattern);
	auto mul_end = std::sregex_iterator();

	i64 result {};
	bool enable {true};
	for (auto it = mul_begin; it != mul_end; ++it) {
		auto& matches = *it;
		if (matches.str() == "do()") {
			enable = true;
			continue;
		} else if (matches.str() == "don't()") {
			enable = false;
			continue;
		}
		if (!enable) continue;
		result += std::stoi(matches[1]) * std::stoi(matches[2]);
	}
	std::cout << "Result: " << result << " (part two)" << std::endl;
}

}

int main() {
	utils::cd_app_workdir();
	std::string input = utils::read_whole_file("inputs/3.txt");
	aoc::part_one(input);
	aoc::part_two(input);

	return 0;
}
