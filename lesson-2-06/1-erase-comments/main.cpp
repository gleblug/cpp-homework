#include <iterator>
#include <fstream>
#include <string>
#include <iostream>


void erase_comments(std::string & code);

int main(int argc, char ** argv)
{
	std::string filename = argv[1];
	std::fstream fin(filename, std::ios::in);

	std::string code {
		std::istreambuf_iterator < char > (fin),
		std::istreambuf_iterator < char > () };

	erase_comments(code);

	std::fstream fout("result.cpp", std::ios::out);
	fout << code;

	return EXIT_SUCCESS;
}

void erase_comments(std::string & code)
{
	for (auto current = std::begin(code); current != std::end(code); ++current) 
	{
		if (*current == '"')
		{
			for (auto end = std::next(current); end != std::end(code); ++end)
			{
				std::cerr << *end;
				if ((*end == '"') && (*std::next(end, -1) != '\\'))
				{
					current = end;
					break;
				}
			}
		}
			
		if (*current == '/') 
		{
			if (*std::next(current) == '/') 
			{
				for (auto end = current; ; ++end)
					if ((end == std::end(code)) || (*end == '\n'))
					{
						code.erase(current, end);
						break;
					}
			}
			else if (*std::next(current) == '*') 
			{
				for (auto end = current; end != std::end(code); ++end)
				{
					if (std::distance(current, end) > 2)
						if ((*end == '/') && (*std::next(end, -1) == '*'))
						{
							code.erase(current, std::next(end));
							break;
						}
				}
			}
		}

		if (current == std::end(code))
		{
			break;
		}
	}
}