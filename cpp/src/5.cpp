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

int main() {
	utils::cd_app_workdir();
	std::string input = utils::read_whole_file("inputs/5.txt");

	std::unordered_map<u32, std::vector<u32>> page_ordering_rules;
	
	std::vector<std::vector<u32>> updates;
	
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

	u32 total_p1 {}, total_p2 {};
	for (auto& update : updates) {
		auto sort_fn = [&] (auto& p1, auto& p2) {
			if (auto it = page_ordering_rules.find(p1); it != page_ordering_rules.end())
				return std::find(it->second.begin(), it->second.end(), p2) != it->second.end();
			else return false;
		};
		bool is_sorted = std::ranges::is_sorted(update, sort_fn);

		if (is_sorted) {
			total_p1 += update[(update.size()+1)/2-1];
			continue;
		}

		// Part 2
		std::ranges::sort(update, sort_fn);
		total_p2 += update[(update.size()+1)/2-1];
	}

	std::cout << "Total: " << total_p1 << " (part one)" << std::endl;
	std::cout << "Total: " << total_p2 << " (part two)" << std::endl;

	return 0;
}
