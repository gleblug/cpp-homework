#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>

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

    return std::move(random_numbers);
}

void print_result(const std::string& message, const double time)
{
	std::cout
	<< std::setw(30) << std::left << message
	<< std::right << time << " ms"
	<< std::endl; 
}

int main(int argc, char const *argv[])
{
	const size_t num_count = 4e6;
	const size_t exp_count = 10;
	const auto random_numbers(get_random_numbers(num_count));

	// test set
	Timer timer;

	for (int i = 0; i < exp_count; ++i)
	{
		std::set<uint> set;
		timer.start();
		for (int j = 0; j < num_count; ++j)
			set.insert(random_numbers[j]);
		timer.stop();
		std::cerr 
			<< "\r[" << std::string(i, '=') << std::string(exp_count-i-1, ' ') << "] "
			<< i * 10 << "% ";
	}

	print_result("\rFill set av time", timer.elapsed() / 10.0f);


	// test sort vector
	timer.restart();

	for (int i = 0; i < exp_count; ++i)
	{
		std::vector<uint> vec;

		timer.start();
		vec = random_numbers;
		std::sort(std::begin(vec), std::end(vec));
		timer.stop();

		std::cerr 
			<< "\r[" << std::string(i, '=') << std::string(exp_count-i-1, ' ') << "] "
			<< i * 10 << "% ";
	}

	print_result("\rSort vector av time", timer.elapsed() / 10.0f);

/*

Fill set av time             4713.4 ms
Sort vector av time          250.7 ms

Лучшим вариантом оказалось использование std::vector, получается быстрее более, чем в 10 раз.

Компилятор:
g++ (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0

*/

	return 0;
}