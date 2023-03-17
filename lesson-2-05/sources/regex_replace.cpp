#include <iostream>
#include <iterator>
#include <regex>
#include <string>

int main(int argc, char ** argv)
{
	std::string data("there is a subsequence in the substring");

	std::regex pattern(R"((sub)([^ ]*))");

	std::cout << std::regex_replace(data, pattern, "sub-$2") << std::endl;

	std::string result;

	std::regex_replace(std::back_inserter(result), data.begin(), data.end(), pattern, "$2");

	std::cout << result << std::endl;

	return EXIT_SUCCESS;
}
