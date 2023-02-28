#include <iostream>
#include <iomanip>
#include <random>

#include <vector>
#include <set>

#include "../lesson-2-01/timer.hpp"


void fill_random_numbers(uint* random_numbers, size_t N)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 1'000'000'000);

    // std::vector<uint> random_numbers(size);
    for (int i = 0; i < N; ++i)
    	random_numbers[i] = distrib(gen);
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

	uint* random_numbers = new uint[num_count];
	fill_random_numbers(random_numbers, num_count);

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

	delete[] random_numbers;

	return 0;
}