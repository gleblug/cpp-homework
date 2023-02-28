#include <iostream>
#include <string>

#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>

int main(int argc, char ** argv)
{
	//boost::bimap < boost::bimaps::set_of < std::string > ,
	//	boost::bimaps::multiset_of < int > >
	boost::bimap < std::string, int > animals;

	animals.insert({ "cat",    4 });
	animals.insert({ "dog",    4 });
	animals.insert({ "shark",  0 });
	animals.insert({ "spider", 8 });

	std::cout << animals.left.count("cat") << std::endl;
	std::cout << animals.right.count(4)    << std::endl;

	std::cout << std::endl;

	for (auto iterator = animals.begin(); iterator != animals.end(); ++iterator)
	{
		std::cout << iterator->left << " has " << iterator->right << " legs\n";
	}

	system("pause");

	return EXIT_SUCCESS;
}