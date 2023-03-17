#include <iomanip>
#include <iostream>
#include <regex>
#include <string>

bool is_identifier(const std::string & string)
{
	std::regex pattern(R"([_[:alpha:]]\w*)");

	return regex_match(string, pattern);
}

int main(int argc, char ** argv)
{
	std::cout << std::boolalpha;

	std::cout << is_identifier("hello") << std::endl;
	std::cout << is_identifier("21asdsa") << std::endl;
	std::cout << is_identifier("_name") << std::endl;
	std::cout << is_identifier("_1g62") << std::endl;
	std::cout << is_identifier("henl5") << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}