#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

#ifdef __WIN32__
#include <Windows.h>
#endif

namespace fs = std::filesystem;

namespace utils {

static fs::path get_application_path() {
	fs::path path;
#ifdef __WIN32__
	WCHAR path_buffer[MAX_PATH];
	GetModuleFileNameW(NULL, path_path, MAX_PATH);
	path = path_buffer;
#elif defined(__unix__)
	path = fs::canonical("/proc/self/exe");
#endif

	return path.parent_path();
}

void cd_app_workdir() noexcept {
	std::filesystem::current_path(get_application_path());
}

std::string read_whole_file(std::filesystem::path const& file_path) noexcept {
	std::ifstream ifs(file_path);

	if (!ifs) {
		std::cerr << "Error reading file: " << file_path << ": " << std::make_error_code(static_cast<std::errc>(errno)).message() << std::endl;
		std::abort();
	}

	return std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
}

std::size_t lines_count(std::string const& str) noexcept {
	return std::count(str.begin(), str.end(), '\n');
}

}
