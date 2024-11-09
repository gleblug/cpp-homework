#include <algorithm>
#include <fstream>
#include <iterator>
#include <mutex>
#include <vector>
#include <string>
#include <iostream>
#include <atomic>
#include <thread>
#include <filesystem>
#include <algorithm>


void seacher_block(
	std::string::const_iterator first,
	std::string::const_iterator last, 
	std::string const &fragment,
	std::size_t const offset,
	std::vector<size_t> &result, 
	std::mutex &res_mutex)
{
	auto current = first;
	while (std::distance(current, last) > fragment.size())
	{
		auto pos = std::search(current, last, std::cbegin(fragment), std::cend(fragment));
		if (pos != last)
		{
			current = std::next(pos);
			std::lock_guard<std::mutex> lock(res_mutex);
			result.push_back(std::distance(first, pos) + offset);
		} else
			break;
	}
}

std::vector<size_t> search_dna(std::string const &sequence, std::string const &fragment)
{
	auto first = std::cbegin(sequence);
	auto last = std::cend(sequence);

	std::vector<size_t> result;
	std::mutex res_mutex;

	const size_t length = std::distance(first, last);
	const size_t frag_length = fragment.size();
	if (!length || !frag_length)
		return result;

	const size_t min_per_thread = 25;
	const size_t max_threads =
		(length + min_per_thread - 1) / min_per_thread;
	const size_t hardware_threads =
		std::thread::hardware_concurrency();

	const size_t num_threads =
		std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

	std::vector <std::jthread> threads(num_threads - 1);

	const size_t block_size = length / num_threads + frag_length - 1;

	auto block_start = first;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		const size_t offset = std::distance(first, block_start); 
		auto block_end = block_start;
		std::advance(block_end, block_size);

		threads[i] = std::jthread(seacher_block, block_start, block_end, fragment, offset, std::ref(result), std::ref(res_mutex));

		block_start = block_end;

	}

	seacher_block(block_start, last, fragment, std::distance(first, block_start), result, res_mutex);

	for (auto &th : threads)
		th.join();

	std::sort(std::begin(result), std::end(result));
	return result;
}

template <typename T>
void print_vector(std::vector<T> const &vec)
{
	std::cout << "[";
	for (auto const &v : vec)
		std::cout << v << ", ";
	std::cout << (vec.size() ? "\b\b]" : "]") << std::endl;
}

int main(int argc, char const *argv[])
{
	std::fstream fin("DNA.txt", std::ios::in);
	std::string const sequence {
		std::istreambuf_iterator < char > (fin),
		std::istreambuf_iterator < char > () };

	std::string fragment;

	std::cout << "Enter a fragment to search:\n";
	std::cin >> fragment;

	auto result = search_dna(sequence, fragment);

	std::cout << "Result:\n";
	print_vector(result);

	return 0;
}