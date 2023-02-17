#include <iostream>

#include <boost/circular_buffer.hpp>

int main(int argc, char ** argv)
{
	using circular_buffer = boost::circular_buffer < int > ;

	circular_buffer cb(3);

	cb.push_back(0);
	cb.push_back(1);
	cb.push_back(2);
	cb.push_back(3);

	std::cout << std::boolalpha << cb.is_linearized() << std::endl;

	circular_buffer::array_range array_1, array_2;

	array_1 = cb.array_one();
	array_2 = cb.array_two();

	std::cout << array_1.second << ";" << array_2.second << std::endl;

	cb.linearize();

	array_1 = cb.array_one();
	array_2 = cb.array_two();

	std::cout << array_1.second << ";" << array_2.second << std::endl;

	return EXIT_SUCCESS;
}