#include <chrono>
#include <cstddef>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <random>
#include <vector>

#include "threads_guard.hpp"


void calculate_block(size_t const points_count)
{
	double const r = 1.0;
	std::uniform_real_distribution<> distribution(0.0, r);

	std::random_device rd;
	std::mt19937 gen(rd());

	size_t pi_points_count = 0;
	for (size_t i = 0; i < points_count; ++i)
	{
		double x = distribution(gen);
		double y = distribution(gen);
		if ((x * x + y * y) <= r)
			++pi_points_count;
	}
}

void pi_parallel(size_t const points_count, unsigned int const num_threads)
{
	std::vector < std::thread > threads(num_threads - 1);
	auto const points_per_thread = points_count / num_threads;

	Threads_Guard guard(threads); // !

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		std::packaged_task < void(size_t) > task(calculate_block);

		threads[i] = std::thread(std::move(task), points_per_thread);
	}

	calculate_block(points_per_thread + (points_count % num_threads));

}

int main(int argc, char const *argv[])
{
	size_t const max_points_count = 100'000'000;
	size_t const exp_count = 5;
	size_t const plot_count = 20;
	size_t const step = max_points_count / plot_count;
	auto const hardw_conc = std::thread::hardware_concurrency();

	std::cerr << "points_count";
	for (unsigned int hc = 1; hc <= hardw_conc; ++ hc)
		std::cerr << ",time_" << hc;
	std::cerr << std::endl;

	for (size_t points_count = step; points_count <= max_points_count; points_count += step)
	{
		std::cerr << points_count;
		for (unsigned int hc = 1; hc <= hardw_conc; ++hc)
		{
			std::vector<long> times;
			for (size_t i = 0; i < exp_count; ++i)
			{
				auto t1 = std::chrono::high_resolution_clock::now();
				pi_parallel(points_count, hc);
				auto t2 = std::chrono::high_resolution_clock::now();
				times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());
			}
			std::cerr << ',' << std::accumulate(begin(times), end(times), 0.0) / exp_count;
		}
		std::cerr << std::endl;
	}

	return 0;
}