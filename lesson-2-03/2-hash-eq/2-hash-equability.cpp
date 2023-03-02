#include <cstddef>
#include <iterator>
#include <math.h>
#include <numeric>
#include <sstream>
#include <string>
#include <set>
#include <tuple>
#include <random>
#include <iostream>
#include <chrono>

#include <fstream>
#include <cmath>

#include <boost/container_hash/hash.hpp>
#include <vector>

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
        c = static_cast<char>(letter(e));

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

template <typename T>
std::pair<double, double> standart_deviation(const std::vector<T> &vec)
{
	const double size = vec.size();
	const double mean = 
		std::accumulate(std::begin(vec), std::end(vec), 0.0f) / size;
	if (size <= 1)
		return std::make_pair(mean, 0);

	auto n_variance_func = [&size, &mean](T accumulator, const T &value) -> double
	{
		return accumulator + ((value - mean)*(value - mean));
	};

	const double variance = 
		std::accumulate(std::begin(vec), std::end(vec), 0.0f, n_variance_func) / (size - 1.0f);

	return std::make_pair(mean, std::sqrt(variance / size));
}

int main(int argc, char const *argv[])
{
	const size_t types_count = 3;
	const size_t log_max_num_count = std::stoi(argv[1]);
	const size_t max_num_count = static_cast<size_t>(std::pow(10, log_max_num_count));
	const size_t experiments_count = 20;


	std::cout
		<< "Count of collizions at " << types_count << " different values types\n"
		<< "and " << experiments_count << " experiments of each iteration:\n\n"
		<< "num_count,\tmean_coll,\tstd_deviation\n";

	for (size_t i = 0; i < max_num_count; i += 500)
	{
		const size_t each_num_count = i / 3;

		std::vector<size_t> collizion_data;

		for (size_t j = 0; j < experiments_count; ++j)
		{
			size_t collizion_counter = 0;
			collizion_counter += collizions_number<int>(each_num_count + 1);
			collizion_counter += collizions_number<float>(each_num_count);
			collizion_counter += collizions_number<std::string>(each_num_count);
			
			collizion_data.push_back(collizion_counter);
		}

		auto [mean, std_dev] = standart_deviation(collizion_data);

		std::cout 
			<< i << "\t\t"
			<< mean << "\t\t" 
			<< std_dev << "\n";
	}

	return 0;
}