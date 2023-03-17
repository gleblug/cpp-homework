#include <algorithm>
#include <iostream>
#include <regex>
#include <string>

int main(int argc, char ** argv)
{
	std::string data = R"(daniel-1; 
		chris-11,		marta-111)";

	std::regex pattern_1(R"(([[:alpha:]]+)-(\d+))");
	std::regex pattern_2("[ \t\n]*[,;.][ \t\n]*");

	std::copy(
		std::sregex_token_iterator(data.begin(), data.end(), pattern_1, { 1, 2 }),
		std::sregex_token_iterator(),
		std::ostream_iterator < std::string >(std::cout, "\n"));

	std::cout << std::endl;

	std::copy(
		std::sregex_token_iterator(data.begin(), data.end(), pattern_2, { -1 }),
		std::sregex_token_iterator(),
		std::ostream_iterator < std::string >(std::cout, "\n"));

	return EXIT_SUCCESS;
}