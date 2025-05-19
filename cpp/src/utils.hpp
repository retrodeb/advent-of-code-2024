#ifndef AOC_UTIL_HPP
#define AOC_UTIL_HPP

#include <string>
#include <filesystem>

#include "ints.hpp"
namespace utils {

void cd_app_workdir() noexcept;
std::string read_whole_file(std::filesystem::path const& file_path) noexcept;
std::size_t lines_count(std::string const& str) noexcept;

}

#endif
