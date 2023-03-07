#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main(int argc, char ** argv)
{
	std::vector < std::string > vector;

	std::copy(
		std::istream_iterator < std::string > (std::cin),
		std::istream_iterator < std::string > (),
		std::back_inserter(vector));

	std::sort(vector.begin(), vector.end());

	std::unique_copy(vector.cbegin(), vector.cend(),
		std::ostream_iterator < std::string > (std::cout, "\n"));

	system("pause");

	return EXIT_SUCCESS;
}