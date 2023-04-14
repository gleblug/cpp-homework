#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

template < typename Iterator, typename F >
void parallel_for_each(Iterator first, Iterator last, F function)
{
	const std::size_t length = std::distance(first, last);

	const std::size_t max_size = 25;

	if (length <= max_size)
		std::for_each(first, last, function);
	else
	{
		Iterator middle = first;
		std::advance(middle, length / 2);

		std::future < void > first_half_result =
			std::async(parallel_for_each < Iterator, F >, first, middle, function);

		parallel_for_each(middle, last, function);
		first_half_result.wait();
	}
}

int main(int argc, char ** argv)
{
	std::vector < int > v(1000'000);
	std::iota(v.begin(), v.end(), 1);

	std::for_each_n(begin(v), 40, [](int n){ std::cout << n << ' '; });
	std::cout << std::endl;
	parallel_for_each(begin(v), end(v), [](int &n){ n++; });
	std::for_each_n(begin(v), 40, [](int n){ std::cout << n << ' '; });
	std::cout << std::endl;

	return EXIT_SUCCESS;
}