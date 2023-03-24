#include <bitset>
#include <iomanip>
#include <iostream>
#include <sstream>

int main(int argc, char ** argv)
{
	std::ostringstream sout;

	sout << "dec: " << 15 << std::hex << " hex: " << 15 << std::endl;

	std::cout << sout.str() << std::endl;

	std::bitset < 15 > b(5789);

	sout << "float: " << 4.67 << " bitset: " << b << std::endl;

	sout.seekp(0);

	sout << "oct: " << std::oct << 15;

	std::cout << sout.str() << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}
