#include <chrono>
#include <ctime>
#include <iomanip>
#include <ios>
#include <iostream>
#include <filesystem>
#include <ostream>


using namespace std::literals;

template <typename TP>
std::time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
              + system_clock::now());
    return system_clock::to_time_t(sctp);
}

void view_directory(const std::filesystem::path & path, const bool is_recursive, const int tab = 0)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (const auto & entry : std::filesystem::directory_iterator(path))
		{
			const auto file_name = entry.path().filename().string();
			const bool is_directory = std::filesystem::is_directory(entry);
			const std::time_t last_write_time = to_time_t(std::filesystem::last_write_time(entry));

			auto filename_str = std::string(tab, ' ') + file_name + (is_directory ? "/" : "");
			auto time_str = std::put_time(std::localtime(&last_write_time), "%F %T");

			std::cout << time_str << std::string(2, ' ') << filename_str << std::endl;

			if (is_directory && is_recursive)
				view_directory(entry.path(), is_recursive, tab + 4);
		}
	}
}

int main(int argc, char const *argv[])
{
	bool is_recursive = false;
	std::string path;

	for (int i = 0; i < argc; ++i)
	{
		std::string arg = argv[i];
		if (arg == "-r")
			is_recursive = true;
		else
			path = arg;
	}

	view_directory(path, is_recursive);

	return 0;
}