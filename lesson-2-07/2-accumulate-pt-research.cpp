#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include "threads_guard.hpp"


template < typename Iterator, typename T >
struct accumulate_block
{
	T operator()(Iterator first, Iterator last)
	{
		return std::accumulate(first, last, T());
	}
};

template < typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init, size_t num_threads)
{
	const std::size_t length = std::distance(first, last);

	if (!length)
		return init;

	else if (num_threads == 1)
		return accumulate_block<Iterator, T>()(first, last) + init;

	const std::size_t block_size = length / num_threads;

	std::vector < std::future < T > > futures(num_threads - 1);
	std::vector < std::thread >		  threads(num_threads - 1);

	Threads_Guard guard(threads);

	Iterator block_start = first;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);

		std::packaged_task < T(Iterator, Iterator) > task{
			accumulate_block < Iterator, T >() };

		futures[i] = task.get_future();
		threads[i] = std::thread(std::move(task), block_start, block_end);

		block_start = block_end;
	}

	T last_result = accumulate_block < Iterator, T > ()(block_start, last);

	T result = init;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		result += futures[i].get();
	}

	result += last_result;

	return result;
}

int main(int argc, char ** argv)
{
	size_t const max_num_threads = 12;
	size_t const exp_count = 20;

	std::vector < int > v(100'000'000);
	std::iota(v.begin(), v.end(), 1);

	std::cerr << "num_threads,time\n";
	
	for (size_t num_threads = 1; num_threads <= max_num_threads; ++num_threads)
	{
		std::cerr << num_threads;

		std::vector<long> times;
		for (size_t i = 0; i < exp_count; ++i)
		{
			/* 
			При измерении времени не использовал оптимизацию -O3, так как она 
			давала одно и то же время при разном количестве потоков. Видимо,
			происходит автоматическое распараллеливание?
			*/
			auto t1 = std::chrono::high_resolution_clock::now();
			parallel_accumulate(v.begin(), v.end(), 0, num_threads);
			auto t2 = std::chrono::high_resolution_clock::now();
			times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());
		}
		std::cerr << ',' << std::accumulate(cbegin(times), cend(times), 0.0) / exp_count << std::endl;
	}

	return 0;
}