#include <iostream>
#include <iterator>

int main(int argc, char ** argv)
{
	std::istreambuf_iterator < char > istreambuf_iterator(std::cin);

	std::istreambuf_iterator < char > end;

	std::ostreambuf_iterator < char > ostreambuf_iterator(std::cout);

	while (istreambuf_iterator != end) 
	{
		*ostreambuf_iterator = *istreambuf_iterator;
		++istreambuf_iterator;
		++ostreambuf_iterator;
	}

	system("pause");

	return EXIT_SUCCESS;
}
