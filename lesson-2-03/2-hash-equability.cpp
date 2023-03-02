#include <cstddef>
#include <sstream>
#include <string>
#include <set>
#include <tuple>
#include <random>
#include <iostream>
#include <chrono>

#include <boost/container_hash/hash.hpp>

template <typename T>
T get_random_value()
{
	return T(get_random_value<int>());
}

// int
template <>
int get_random_value<>()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(-2'147'483'648, 2'147'483'647);

	return distrib(gen);
}

// double
template <>
double get_random_value<>()
{
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(-1e9, 1e9);

	return distrib(gen);
}

// string
template <>
std::string get_random_value<>()
{
	const std::size_t length = 8;
    std::uniform_int_distribution <> letter(97, 122);
    std::default_random_engine e(static_cast < std::size_t > (
    std::chrono::system_clock::now().time_since_epoch().count()));

    std::string string(length, ' ');

    for (auto & c : string)
        c = letter(e);

    return string;
}

template <typename T>
size_t collizions_number(const size_t num_count)
{
	std::set<size_t> hash_container;
	size_t collizion_counter = 0;
	
	for (std::size_t i = 0; i < num_count; ++i)
	{
		auto [it, is_collision] 
			= hash_container.insert(boost::hash_value(get_random_value<T>()));
		if (!is_collision)
			++collizion_counter;
	}

	return collizion_counter;
}


int main(int argc, char const *argv[])
{
	const size_t types_count = 3;
	const size_t num_count = std::stoi(argv[1]) / 3;
	size_t all_collizion_counter = 0;

	all_collizion_counter += collizions_number<int>(num_count);
	all_collizion_counter += collizions_number<float>(num_count);
	all_collizion_counter += collizions_number<std::string>(num_count);

	std::cout 
		<< "Count of collizions at " << num_count * types_count << " different values:\n"
		<< all_collizion_counter << std::endl;

	return 0;
}