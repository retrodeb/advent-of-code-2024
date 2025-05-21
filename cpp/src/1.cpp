#include "utils.hpp"
#include "ints.hpp"

#include <filesystem>
#include <cstdint>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>
#include <ranges>
#include <charconv>
#include <algorithm>

namespace aoc {

using LocationID = u64;
using LocationList = std::pair<std::vector<LocationID>, std::vector<LocationID>>;

LocationList parse(std::string const& input) {
	LocationList list;
	{
		u32 n_lines = std::ranges::count(input, '\n');
		list.first.reserve(n_lines);
		list.second.reserve(n_lines);
	}

	for (u32 line_number {1}; const auto line : input | std::views::split('\n')) {
		auto numbers = std::views::split(line, std::string_view("   "));

		if (std::ranges::distance(numbers) != 2) continue;

		auto first = *(numbers).begin();
		auto second = *(numbers | std::views::drop(1)).begin();

		LocationID l_id1, l_id2;
		if (std::from_chars(&*first.begin(), &*first.end(), l_id1).ec != std::errc() ||
			std::from_chars(&*second.begin(), &*second.end(), l_id2).ec != std::errc()) {
			std::cerr << "Error parsing line: " << line_number << std::endl;
			std::abort();
		}
		list.first.push_back(l_id1);
		list.second.push_back(l_id2);
		line_number++; // We have no std::ranges::enumerate in C++20
	}
	return list;
}

void sort_list(LocationList& list) {
	std::ranges::sort(list.first);
	std::ranges::sort(list.second);	
}


void part_one(LocationList list) { // Copy list
	sort_list(list);
	u64 total_distance {};
	for (u64 i {}; i<list.first.size(); i++) {
		auto l_id1 = list.first[i];
		auto l_id2 = list.second[i];

		total_distance += std::max(l_id1, l_id2) - std::min(l_id1, l_id2);;
	}

	std::cout << "Total distance is: " << total_distance << std::endl;
}

void part_two(LocationList list) { // Copy list
	sort_list(list);

	u64 similarity {};
	for (auto id : list.first)
		similarity += id * std::ranges::count(list.second, id);

	std::cout << "Similarity score is: " << similarity << std::endl;
}

}


int main() {
	utils::cd_app_workdir();
	auto list = aoc::parse(utils::read_whole_file("./inputs/1.txt"));
	aoc::part_two(list);
	aoc::part_one(list);

	return 0;
}
