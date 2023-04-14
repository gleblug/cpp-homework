#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>

#include <filesystem>
#include <fstream>
#include <iterator>

int main(int argc, char const *argv[])
{
	const std::filesystem::path path("file");
	const size_t size = 1024;

	// std::ofstream file(path);
	// std::fill_n(std::ostream_iterator<char>(file), size, '\0');
	// file.close();

	boost::interprocess::managed_mapped_file manmap_file(
		boost::interprocess::open_or_create,
		path.c_str(),
		size
	); 

	manmap_file.construct<int>("integer1")(42);
	manmap_file.construct<char>("char1")('b');
	
	return 0;
}