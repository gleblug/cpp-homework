#include <algorithm>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <cstring>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <iterator>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>


int main(int argc, char const *argv[])
{
	const std::filesystem::path path = "file";
	const size_t size = 1024;

	std::ofstream file(path, std::ios::trunc | std::ios::binary);
	std::fill_n(std::ostream_iterator<char>(file), size, '\0');
	file.close();

	std::cin.get();

	// shared memory
	boost::interprocess::file_mapping f_map(path.c_str(), boost::interprocess::read_write);
	boost::interprocess::mapped_region map_reg(f_map, boost::interprocess::read_write);

	std::cout << map_reg.get_size() << std::endl;

	// fill file
	std::memset(map_reg.get_address(), 'A', size);

	boost::interprocess::file_mapping::remove(path.c_str());
	return 0;
}