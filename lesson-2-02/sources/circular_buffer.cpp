#include <iostream>

#include <boost/circular_buffer.hpp>

int main(int argc, char ** argv)
{
	using circular_buffer = boost::circular_buffer < int > ;

	circular_buffer cb(3);

	std::cout << "capacity: " << cb.capacity() << std::endl;
	std::cout << "size: " << cb.size() << std::endl;

	cb.push_back(0);
	cb.push_back(1);
	cb.push_back(2);

	std::cout << "size: " << cb.size() << std::endl;

	cb.push_back(3);
	cb.push_back(4);
	cb.push_back(5);

	std::cout << "size: " << cb.size() << std::endl;

	for (int i : cb)
	{
		std::cout << i << std::endl;
	}
		
	return EXIT_SUCCESS;
}