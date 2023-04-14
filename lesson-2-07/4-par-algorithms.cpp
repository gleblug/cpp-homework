#include "pstl/glue_execution_defs.h"
#include <algorithm>
#include <functional>
#include <iterator>
#include <math.h>
#include <numeric>
#include <tuple>
#include <type_traits>
#include <vector>
#include <chrono>
#include <iostream>
#include <execution>
#include <cmath>

enum class Algorithms{ for_each, partial_sum, inclusive_scan, inner_product, transform_reduce };

using vec_it_t = std::vector<double>::iterator;
using unary_op_t = double (double);
using binary_op_t = double (double, double);


template <Algorithms alg_type, typename Policy>
void run_algorithm(vec_it_t begin, vec_it_t end) 
{
	constexpr Policy policy{};
	std::function<unary_op_t> unary_op( [](double n){ return tanh(n); } );
	std::function<binary_op_t> binary_op( [](double a, double b ){ return exp(a) + exp(b); } );

	switch (alg_type) {
	case Algorithms::for_each:
		std::for_each(policy, begin, end, unary_op);
		break;

	case Algorithms::partial_sum:
		std::partial_sum(begin, end, begin, binary_op);
		break;

	case Algorithms::inclusive_scan:
		std::inclusive_scan(policy, begin, end, begin, binary_op);
		break;

	case Algorithms::inner_product:
		std::inner_product(begin, end, begin, 0.0, binary_op, binary_op);
		break;

	case Algorithms::transform_reduce:
		std::transform_reduce(policy, begin, end, 0.0, binary_op, unary_op);
		break;

	default:
		break;
	}
}


template <Algorithms alg_type, typename Policy = std::execution::sequenced_policy>
double measure_time(size_t const points_count)
{
	size_t const exp_count = 5;

	std::vector<long> times;
	for (size_t i = 0; i < exp_count; ++i)
	{
		std::vector < double > vec(points_count);
		std::iota(begin(vec), end(vec), 1);

		auto t1 = std::chrono::high_resolution_clock::now();
		run_algorithm<alg_type, Policy>(begin(vec), end(vec));
		auto t2 = std::chrono::high_resolution_clock::now();

		times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());
	}
	return std::accumulate(begin(times), end(times), 0.0) / exp_count;
}



int main(int argc, char const *argv[])
{
	size_t const max_points_count = 100'000'000;
	size_t const plot_count = 10;
	size_t const step = max_points_count / plot_count;

	std::cerr 
		<< "points_count,"
		<< "for_each seq,for_each par,for_each par_unsec,for_each unsec,"
		<< "partial_sum,"
		<< "inclusive_scan seq,inclusive_scan par,inclusive_scan par_unsec,inclusive_scan unsec,"
		<< "inner_product,"
		<< "transform_reduce seq,transform_reduce par,transform_reduce par_unsec,transform_reduce unsec"
	<< std::endl;

	for (size_t points_count = step; points_count <= max_points_count; points_count += step)
	{
		std::cerr
			<< points_count << ','
			<< measure_time<Algorithms::for_each, std::execution::sequenced_policy>(points_count) << ','
			<< measure_time<Algorithms::for_each, std::execution::parallel_policy>(points_count) << ','
			<< measure_time<Algorithms::for_each, std::execution::parallel_unsequenced_policy>(points_count) << ','
			<< measure_time<Algorithms::for_each, std::execution::unsequenced_policy>(points_count) << ','

			<< measure_time<Algorithms::partial_sum>(points_count / 4) << ','

			<< measure_time<Algorithms::inclusive_scan, std::execution::sequenced_policy>(points_count / 4) << ','
			<< measure_time<Algorithms::inclusive_scan, std::execution::parallel_policy>(points_count / 4) << ','
			<< measure_time<Algorithms::inclusive_scan, std::execution::parallel_unsequenced_policy>(points_count / 4) << ','
			<< measure_time<Algorithms::inclusive_scan, std::execution::unsequenced_policy>(points_count / 4) << ','

			<< measure_time<Algorithms::inner_product>(points_count / 4) << ','

			<< measure_time<Algorithms::transform_reduce, std::execution::sequenced_policy>(points_count / 4) << ','
			<< measure_time<Algorithms::transform_reduce, std::execution::parallel_policy>(points_count / 4) << ','
			<< measure_time<Algorithms::transform_reduce, std::execution::parallel_unsequenced_policy>(points_count / 4) << ','
			<< measure_time<Algorithms::transform_reduce, std::execution::unsequenced_policy>(points_count / 4) << '\n';
	}


	return 0;
}