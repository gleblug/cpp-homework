#include <boost/interprocess/creation_tags.hpp>
#include <iostream>
#include <string>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>


int main(int argc, char const *argv[])
{
	boost::interprocess::shared_memory_object shared_memory(
		boost::interprocess::open_or_create, 
		"C++", 
		boost::interprocess::read_write
	);

	shared_memory.truncate(1024);
	boost::interprocess::offset_t size;
	shared_memory.get_size(size);

	std::cout << shared_memory.get_name() << " " << size << std::endl;


	boost::interprocess::mapped_region mapped_region(
		shared_memory,
		boost::interprocess::read_write
	);

	std::cout << mapped_region.get_size() << " " << mapped_region.get_address() << std::endl;

	int *ptr = static_cast<int *>(mapped_region.get_address());

	while (std::cin >> (*ptr));

	boost::interprocess::shared_memory_object::remove("C++");
	return 0;
}