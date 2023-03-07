#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <vector>

int main(int argc, char ** argv)
{
	std::list < int > list = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	std::vector < int > vector;

	copy(list.cbegin(), list.cend(), back_inserter(vector));

	std::deque < int > deque;

	copy(list.cbegin(), list.cend(), front_inserter(deque));

	std::set < int > set;

	copy(list.cbegin(), list.cend(), inserter(set, set.begin()));

	system("pause");

	return EXIT_SUCCESS;
}