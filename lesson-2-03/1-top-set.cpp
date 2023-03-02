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
	std::cerr
		<< std::setw(30) << std::left << message
		<< std::right << time << " ms"
		<< std::endl; 
}

void test_set_fill(const size_t exp_count, const std::vector<uint> &templ)
{
	// test set
	Timer timer;

	for (int i = 0; i < exp_count; ++i)
	{
		std::set<uint> set;
		timer.start();
		for (const auto &t : templ)
			set.insert(t);
		timer.stop();
		std::cerr 
			<< "\r[" << std::string(i, '=') << std::string(exp_count-i-1, ' ') << "] "
			<< i * 100 / exp_count << "% ";
	}

	print_result("\rFill set av time", timer.elapsed() / static_cast<double>(exp_count));
}

void test_vector_sort(const size_t exp_count, const std::vector<uint> &templ)
{
	// test sort vector
	Timer timer;

	for (int i = 0; i < exp_count; ++i)
	{
		std::vector<uint> vec;

		timer.start();
		vec = templ;
		std::sort(std::begin(vec), std::end(vec));
		timer.stop();

		std::cerr 
			<< "\r[" << std::string(i, '=') << std::string(exp_count-i-1, ' ') << "] "
			<< i * 100 / exp_count << "% ";
	}

	print_result("\rSort vector av time", timer.elapsed() / static_cast<double>(exp_count));
}


int main(int argc, char const *argv[])
{
	const size_t num_count = 4e6;
	const size_t exp_count = 20;
	const auto random_numbers(get_random_numbers(num_count));

	test_set_fill(exp_count, random_numbers);

	test_vector_sort(exp_count, random_numbers);
/*

Fill set av time             4867.3 ms
Sort vector av time           282.5 ms

Лучшим вариантом оказалось использование std::vector, получается быстрее более, чем в 10 раз.

Компилятор:
g++ (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0

*/

	return 0;
}