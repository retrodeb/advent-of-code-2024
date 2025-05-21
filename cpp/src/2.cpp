#include "utils.hpp"
#include "ints.hpp"

#include <iostream>
#include <string>
#include <string_view>
#include <ranges>
#include <array>
#include <vector>
#include <charconv>
#include <algorithm>

namespace aoc {

using Level = u32;
constexpr u32 MaxLevels {16};

struct Report {
	std::array<Level, MaxLevels> levels;
	u32 levels_count;
	bool safe;
	bool increasing;
};

using Reports = std::vector<Report>;

Reports parse(std::string const& input) {
	Reports reports;
	reports.reserve(utils::lines_count(input));

	// Parse input
	for (u32 line_number {1}; auto line : input | std::views::split('\n')) {
		auto level_split = line | std::views::split(' ');

		u32 levels_count = std::ranges::distance(level_split);
		if (levels_count == 0) continue;
		
		if (levels_count > MaxLevels) {
			std::cerr << "Error, MaxLevels is set to " << MaxLevels << std::endl;
			std::abort();
		}
		
		auto& report = reports.emplace_back();
		report.levels_count = levels_count;
		for (u8 i {}; auto level : level_split) {
			if (std::from_chars(&*level.begin(), &*level.end(), report.levels[i]).ec != std::errc()) {
				std::cerr << "Error parsing line: " << line_number << std::endl;
				std::abort();
			}
			i++;
		}
		
		line_number++; // We have no std::ranges::enumerate in C++20
	}
	return reports;
}

void part_one(Reports& reports) {
	for (auto& report : reports) {
		report.safe = true;
		for (u8 i=1; i<report.levels_count; i++) {
			auto level_a = report.levels[i-1];
			auto level_b = report.levels[i];
			bool increasing = level_a > level_b;
			if (i == 1) report.increasing = increasing;
			u32 diff = std::max(level_a, level_b) - std::min(level_a, level_b);
			if (
				(diff > 3 || diff == 0) ||
				(increasing != report.increasing)
			) {
				report.safe = false;
				break;
			}
		}
	}

	auto safe_reports_count = std::ranges::count_if(reports, [] (auto const& report) { return report.safe; });
	std::cout << safe_reports_count << " safe reports found! (part one)" << std::endl;
}

void part_two(Reports& reports) {
	for (auto& report : reports) {
		report.safe = true;
		for (u8 i=1,err=0; i<report.levels_count; i++) {
			auto level_a = report.levels[i-1];
			auto level_b = report.levels[i];
			bool increasing = level_a > level_b;
			if (i == 1 || (i == 2 && err == 1)) report.increasing = increasing;
			u32 diff = std::max(level_a, level_b) - std::min(level_a, level_b);
			if (((diff > 3 || diff == 0) ||
				 (increasing != report.increasing)) && err++ == 1) {
				report.safe = false;
				break;
			}
		}
	}

	auto safe_reports_count = std::ranges::count_if(reports, [] (auto const& report) { return report.safe; });
	std::cout << safe_reports_count << " safe reports found! (part two)" << std::endl;
}

}

int main() {
	utils::cd_app_workdir();
	
	auto reports = aoc::parse(utils::read_whole_file("./inputs/2.txt"));
	aoc::part_one(reports);
	aoc::part_two(reports);
	
	return 0;
}
