#include <iostream>
#include <random>
#include <algorithm>

#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>

#include "../lesson-2-01/timer.hpp"


template <typename T, typename Ref>
Timer::time_t member_sort_time(Ref const &ref_array)
{
	Timer timer;
	T array(ref_array.size());
	std::copy(std::begin(ref_array), std::end(ref_array), std::begin(array));

	timer.start();
	array.sort();
	timer.stop();

	return timer.elapsed();
}

template <typename T, typename Ref>
Timer::time_t standart_sort_time(Ref const &ref_array)
{
	Timer timer;
	T array(ref_array.size());
	std::copy(std::begin(ref_array), std::end(ref_array), std::begin(array));

	timer.start();
	std::sort(std::begin(array), std::end(array));
	timer.stop();

	return timer.elapsed();
}

template <typename Ref>
Timer::time_t array_sort_time(Ref const& ref_array)
{
	Timer timer;
	Ref array(ref_array);

	timer.start();
	std::sort(std::begin(array), std::end(array));
	timer.stop();

	return timer.elapsed();
}

void test_containers()
{	
	using container_type = int;

	const size_t container_size = 1e6;
	const int max_number = 1e8;
	const size_t container_count = 5;
	
	using array_t 			= std::array<container_type, container_size>;
	using vector_t 			= std::vector<container_type>;
	using deque_t 			= std::deque<container_type>;
	using list_t 			= std::list<container_type>;
	using forward_list_t 	= std::forward_list<container_type>;

	array_t reference_array;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(1, max_number);
    
    std::generate(std::begin(reference_array), std::end(reference_array), [&](){ return distribution(rng); });


    const size_t exp_count = 10;

    Timer::time_t array_time, vector_time, deque_time, list_time, forward_list_time;
    for (int i = 0; i < exp_count; ++i)
    {
    	array_time 			+= array_sort_time<array_t>(reference_array);
		vector_time 		+= standart_sort_time<vector_t>(reference_array);
		deque_time 			+= standart_sort_time<deque_t>(reference_array);
		list_time 			+= member_sort_time<list_t>(reference_array);
		forward_list_time 	+= member_sort_time<forward_list_t>(reference_array);
    }

    array_time /= exp_count;
    vector_time /= exp_count;
    deque_time /= exp_count;
    list_time /= exp_count;
    forward_list_time /= exp_count;

    std::cout
    << "| Container    	| Sort time, ms | Sort type 	|\n"
	<< "|--------------	|---------------|---------------|\n"
	<< "| Array        	| " << array_time 			<< "\t\t| Standart  	|\n"
	<< "| Vector       	| " << vector_time          << "\t\t| Standart  	|\n"
	<< "| Deque        	| " << deque_time           << "\t\t| Standart  	|\n"
	<< "| List         	| " << list_time            << "\t\t| Member-fun 	|\n"
	<< "| Forward list 	| " << forward_list_time    << "\t\t| Member-fun 	|\n"
	<< std::endl;
}


int main(int argc, char const *argv[])
{
	test_containers();

	return 0;
}