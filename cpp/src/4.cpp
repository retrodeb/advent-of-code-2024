#include "utils.hpp"

#include <iostream>
#include <ranges>
#include <algorithm>
#include <utility>

int main() {
	utils::cd_app_workdir();
	std::string input = utils::read_whole_file("inputs/4.txt");
	
	auto width = input.find('\n');
	auto height = std::ranges::count(input, '\n');
	for (auto line : input | std::views::split('\n') | std::views::take(height-1)) {
		if (line.size() != width) {
			std::cerr << "Input line width must be: " << width << std::endl;
			std::abort();
		}
	}

	auto get_char = [&input, width] (u32 x, u32 y) -> char {
		return input.at(y * (width+1) + x);
	};

	auto check_match = [width, height, &get_char] (std::string_view xmas, u32 x, u32 y, i8 add_x, i8 add_y) {
		u32 last_x = x + (static_cast<i64>(xmas.size())-1) * add_x;
		u32 last_y = y + (static_cast<i64>(xmas.size())-1) * add_y;
		if (
			(x >= width) ||
			(y >= height) ||
			(last_x >= width) ||
			(last_y >= height)
		) return false;
		
		for (u32 i=0; i<xmas.size(); i++) {
			if (xmas[i] != get_char(x, y)) return false;
			x += add_x; y += add_y;
		}
		return true;
	};

	{
		// Part one
		std::string_view xmas = "XMAS";
		u32 xmas_count {};

		for (u32 y{}; y<height; ++y) {
			for (u32 x{}; x<width; ++x) {
				if (check_match(xmas, x, y,  1,  0)) ++xmas_count;
				if (check_match(xmas, x, y, -1,  0)) ++xmas_count;
				if (check_match(xmas, x, y,  0,  1)) ++xmas_count;
				if (check_match(xmas, x, y,  0, -1)) ++xmas_count;
				if (check_match(xmas, x, y,  1,  1)) ++xmas_count;
				if (check_match(xmas, x, y,  1, -1)) ++xmas_count;
				if (check_match(xmas, x, y, -1,  1)) ++xmas_count;
				if (check_match(xmas, x, y, -1, -1)) ++xmas_count;
			}
		}

		std::cout << "XMAS count: " << xmas_count << " (part one)" << std::endl;
	}

	{
		// Part two
		u32 xmas_count {};
		std::string_view xmas = "MAS";

		for (u32 y{}; y<height; ++y) {
			for (u32 x{}; x<width; ++x) {
				if (
					(check_match(xmas, x-1, y-1,  1, 1) || check_match(xmas, x+1, y+1, -1, -1)) &&
					(check_match(xmas, x-1, y+1,  1, -1) || check_match(xmas, x+1, y-1, -1, 1))
				) ++xmas_count;
			}
		}
		std::cout << "XMAS count: " << xmas_count << " (part two)" << std::endl;
	}

	return 0;
}
