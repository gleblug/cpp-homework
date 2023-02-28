#include <iomanip>
#include <iostream>
#include <iterator>
#include <typeinfo>
#include <unordered_set>
#include <utility>

template < typename T1, typename T2 >
std::ostream & operator << (std::ostream & stream, const std::pair < T1, T2 > p)
{
	return (stream << "[" << p.first << "," << p.second << "]");
}

void print_hash_table_state(const std::unordered_set < int > & unordered_set)
{
	std::cout << "size:            " << unordered_set.size() << std::endl;
	std::cout << "buckets:         " << unordered_set.bucket_count() << std::endl;
	std::cout << "load factor:     " << unordered_set.load_factor() << std::endl;
	std::cout << "max load factor: " << unordered_set.max_load_factor() << std::endl;

	std::cout << std::endl;

	if (typeid(
		typename std::iterator_traits < 
		typename std::unordered_set < int > ::iterator>::iterator_category) == 
		typeid(std::bidirectional_iterator_tag)) 
	{
		std::cout << "chaining style: doubly-linked" << std::endl;
	}
	else 
	{
		std::cout << "chaining style: singly-linked" << std::endl;
	}

	std::cout << std::endl;

	std::cout << "data: " << std::endl;

	for (auto index = 0U; index != unordered_set.bucket_count(); ++index)
	{
		std::cout << " b[" << std::setw(3) << index << "]: ";

		for (auto iterator = unordered_set.begin(index); 
			iterator != unordered_set.end(index); ++iterator)
		{
			std::cout << *iterator << ' ';
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

int main(int argc, char ** argv)
{
	std::unordered_set < int > unordered_set = { 1,2,3,5,7,11,13,17,19 };

	print_hash_table_state(unordered_set);

	unordered_set.rehash(90);

	print_hash_table_state(unordered_set);

	system("pause");

	return EXIT_SUCCESS;
}