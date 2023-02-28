#include <iostream>
#include <iomanip>
#include <random>

#include <vector>
#include <set>

#include "../lesson-2-01/timer.hpp"


std::vector<uint> get_random_numbers(size_t size)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 1'000'000'000);

    std::vector<uint> random_numbers(size);
    for (auto & v : random_numbers)
    	v = distrib(gen);

    return random_numbers;
}

void print_result(const std::string& message, const double time)
{
	std::cout
	<< std::setw(20) << std::left << message
	<< std::right << time << " ms"
	<< std::endl; 
}

int main(int argc, char const *argv[])
{
	const size_t num_count = 4e6;
	const size_t exp_count = 10;
	const auto random_numbers = get_random_numbers(num_count);

	std::cerr << "Complete fill random numbers\n";

	std::set<uint> set;
	std::vector<uint> vec;


	Timer timer;

	// 10 times fill set measured
	for (int i = 0; i < exp_count; ++i)
	{
		timer.start();
		for (int j = 0; j < num_count; ++j)
			set.insert(random_numbers[j]);
		timer.stop();
		set.clear();
		std::cout << i+1 << "/10\n";
	}

	print_result("Fill set av time", timer.elapsed() / 10.0f);

	return 0;
}