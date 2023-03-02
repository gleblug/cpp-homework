#include <cstddef>
#include <set>
#include <iostream>
#include <map>
#include <fstream>
#include <filesystem>
#include <vector>

#include "generator.hpp"
#include "GeneralHashFunctions.h"

std::pair<size_t, size_t> start_values(int argc, char const *argv[])
{
	size_t max_num_count = 10'000;
	size_t step = 500;

	switch (argc) {
	case 1:
		break;
	case 2:
		max_num_count = std::stoi(argv[1]);
		break;
	case 3:
		max_num_count = std::stoi(argv[1]);
		step = std::stoi(argv[2]);
		break;
	}

	return std::make_pair(max_num_count, step);
}

template <typename Func>
size_t collizions_number(const Func &hash_function, const size_t num_count)
{
	auto random_words = make_random_words(num_count, 8);
	std::set<size_t> hash_container;
	size_t collizion_counter = 0;
	
	for (const auto &word : random_words)
	{
		auto [it, is_collision] 
			= hash_container.insert(hash_function(word));
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
	const auto [max_num_count, step] = start_values(argc, argv);
	const size_t experiments_count = 20;

	std::map<std::string, HashFunction> map_hash_functions{
		{"RS-Hash", RSHash},
		{"JS-Hash", JSHash},
		{"PJW-Hash", PJWHash},
		{"ELF-Hash", ELFHash},
		{"BKDR-Hash", BKDRHash},
		{"SDBM-Hash", SDBMHash},
		{"DJB-Hash", DJBHash},
		{"DEK-Hash", DEKHash},
		{"FNV-Hash", FNVHash},
		{"BP-Hash", BPHash},
		{"AP-Hash", APHash}	
	};

	for (auto [name, hash_function] : map_hash_functions)
	{
		std::cout << "Testing " << name << "\n";
		
		std::string dir_name = "data-" + std::to_string(max_num_count) + "-" + std::to_string(step) + "/";
		std::filesystem::create_directory(dir_name);

		std::ofstream file(dir_name	+ name, std::ios::trunc);
		if (!file)
		    throw std::runtime_error("Cannot open file!");

		file << "num_count,mean_coll,std_dev\n";

		for (size_t num_count = 0; num_count < max_num_count; num_count += step)
		{
			std::vector<size_t> collizion_data;

			for (size_t j = 0; j < experiments_count; ++j)
			{
				size_t collizion_counter = 0;
				collizion_counter += collizions_number(hash_function, num_count);
				
				collizion_data.push_back(collizion_counter);
			}

			auto [mean_coll, std_dev] = standart_deviation(collizion_data);
			file << num_count << ',' << mean_coll << ',' << std_dev << '\n';

			size_t N = max_num_count / step - 1;
			size_t i = num_count / step;
			auto progr_sum = [](size_t val){return val * (val - 1) / 2;};
			std::cerr << "\r" << progr_sum(i) * 100 / progr_sum(N) << "% proceed...";
		}

		std::cerr << "\r                        \rComplete!\n\n";
	}


	return 0;
}