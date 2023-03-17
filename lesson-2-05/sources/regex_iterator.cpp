#include <algorithm>
#include <iostream>
#include <regex>
#include <string>

int main(int argc, char ** argv)
{
	std::string data = "abc 1234 def3453ыва 5678 hij";

	std::regex pattern(R"(\s\d{4})");

	std::sregex_iterator begin(data.cbegin(), data.cend(), pattern);
	std::sregex_iterator end;

	std::for_each(begin, end, [](const std::smatch & m)
	{
		std::cout << m[0] << std::endl;
	});

	return EXIT_SUCCESS;
}