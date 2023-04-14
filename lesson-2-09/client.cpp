#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <iostream>
#include <string>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>


int main(int argc, char const *argv[])
{
	boost::interprocess::shared_memory_object shared_memory(
		boost::interprocess::open_only, 
		"C++", 
		boost::interprocess::read_only
	);

	boost::interprocess::mapped_region mapped_region(
		shared_memory,
		boost::interprocess::read_only
	);

	int *ptr = static_cast<int *>(mapped_region.get_address());
	
	std::cout << *ptr << std::endl;

	return 0;
}