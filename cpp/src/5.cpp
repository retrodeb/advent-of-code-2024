#include "utils.hpp"
#include "ints.hpp"

#include <vector>
#include <iostream>
#include <ranges>
#include <string_view>
#include <utility>
#include <array>
#include <charconv>
#include <algorithm>
#include <unordered_map>

namespace aoc {

struct Printer {
	std::unordered_map<u32, std::vector<u32>> page_ordering_rules;
	std::vector<std::vector<u32>> updates;
	
	Printer(std::string input) {
		using std::literals::operator""sv;

		auto input_rules = input | std::views::split("\n\n"sv) | std::views::take(1);
		if (std::ranges::distance(input_rules) != 1) {
			std::cerr << "Error parsing, no rules found" << std::endl;
			std::abort();
		}

		// Parse rules
		for (auto rule : *input_rules.begin() | std::views::split('\n')) {
			auto pages = rule | std::views::split('|');
			if (std::ranges::distance(pages) != 2) continue;

			auto range_x = *(pages).begin();
			auto range_y = *(pages | std::views::drop(1)).begin();

			u32 page_x, page_y;
		
			if (auto ec = std::make_error_code(std::from_chars(&*range_x.begin(), &*range_x.end(), page_x).ec)) {
				std::cerr << "Error parsing ordering rules: " << ec.message() << std::endl;
				std::abort();
			}
		
			if (auto ec = std::make_error_code(std::from_chars(&*range_y.begin(), &*range_y.end(), page_y).ec)) {
				std::cerr << "Error parsing ordering rules: " << ec.message() << std::endl;
				std::abort();
			}
		
			auto [it, inserted] = page_ordering_rules.try_emplace({page_x});
			if (inserted) it->second.reserve(32);
			it->second.push_back(page_y);
		}
	
		auto updates_range = input | std::views::split("\n\n"sv) | std::views::drop(1) | std::views::take(1);
	
		if (std::ranges::distance(updates_range) != 1) {
			std::cerr << "Error parsing, no updates found" << std::endl;
			std::abort();
		}
		auto updates_range_split = *updates_range.begin() | std::views::split('\n');
		updates.reserve(std::ranges::distance(updates_range_split));
	
		// Parse updates
		for (auto update_range : updates_range_split) {
			auto pages_range = update_range | std::views::split(',');
			auto pages_count = std::ranges::distance(pages_range);
			if (pages_count == 0) continue;
		
			if ((pages_count % 2) == 0) {
				std::cerr << "Invalid number of pages to print, must be odd" << std::endl;
				std::abort();
			}
		
			auto& update = updates.emplace_back();
			update.reserve(std::ranges::distance(pages_range));
			for (auto page_range : pages_range) {
				auto& page = update.emplace_back();
				if (auto ec = std::make_error_code(std::from_chars(&*page_range.begin(), &*page_range.end(), page).ec)) {
					std::cerr << "Error parsing update: " << ec.message() << std::endl;
					std::abort();
				}
			}
		}
	}

	auto get_sort_fn() const {
		return [&] (auto const& p1, auto const& p2) {
			if (auto it = page_ordering_rules.find(p1); it != page_ordering_rules.cend())
				return std::find(it->second.cbegin(), it->second.cend(), p2) != it->second.cend();
			else return false;
		};
	}
};

void part_one(Printer const& printer) {
	u32 total {};
	for (auto const& update : printer.updates) {
		bool is_sorted = std::ranges::is_sorted(update, printer.get_sort_fn());
		if (!is_sorted) continue;
		total += update[(update.size()+1)/2-1];
	}

	std::cout << "Total: " << total << " (part one)" << std::endl;
}

void part_two(Printer const& printer) {
	u32 total {};
	for (auto const& update : printer.updates) {
		bool is_sorted = std::ranges::is_sorted(update, printer.get_sort_fn());
		if (is_sorted) continue;

		auto sorted_update = update; // Copy update
		std::ranges::sort(sorted_update, printer.get_sort_fn());
		
		// Part 2
		total += sorted_update[(sorted_update.size()+1)/2-1];
	}

	std::cout << "Total: " << total << " (part two)" << std::endl;
}

}

int main() {
	utils::cd_app_workdir();
	aoc::Printer printer(utils::read_whole_file("inputs/5.txt"));
	aoc::part_one(printer);
	aoc::part_two(printer);
	return 0;
}
