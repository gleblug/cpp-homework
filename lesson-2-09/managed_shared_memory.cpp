
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <string>


int main(int argc, char const *argv[])
{
	const std::string mem_name = "managed_memory";
	const std::string var_name = "integer1";
	const size_t size = 1024;

	boost::interprocess::managed_shared_memory mansh_memory(
		boost::interprocess::open_or_create,
		mem_name.c_str(),
		size
	);

	int *it = mansh_memory.construct<int>(var_name.c_str())[10](42);
	auto [ptr, n] = mansh_memory.find<int>(var_name.c_str());


	boost::interprocess::shared_memory_object::remove(mem_name.c_str());
	return 0;
}