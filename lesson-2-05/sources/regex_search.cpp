#include <iostream>
#include <regex>
#include <string>

int main(int argc, char ** argv)
{
	// Почтовый код США: XXddddd-dddd
	std::regex pattern(R"(\w{2}\s*\d{5}(-\d{4})?)");

	for (std::string line; getline(std::cin, line); )
	{
		std::smatch matches;

		if (std::regex_search(line, matches, pattern))
		{
			for (std::size_t i = 0; i < matches.size(); ++i)
			{
				std::cout << matches[i] << " | ";
			}

			std::cout << std::endl;
		}
	}

	return EXIT_SUCCESS;
}