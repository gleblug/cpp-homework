#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main(int argc, char ** argv)
{
	std::vector < int > m_1 = { 1, 2, 2, 4, 6, 7, 7, 9 };
	std::vector < int > m_2 = { 2, 2, 2, 3, 6, 6, 8, 9 };

	std::cout << "m_1: ";
	std::copy(m_1.cbegin(), m_1.cend(), 
		std::ostream_iterator < int > (std::cout, " "));
	std::cout << std::endl;
	std::cout << "m_2: ";
	std::copy(m_2.cbegin(), m_2.cend(),
		std::ostream_iterator < int > (std::cout, " "));
	std::cout << std::endl << std::endl;

	std::cout << "merge(): ";
	std::merge(
		m_1.cbegin(), m_1.cend(),
		m_2.cbegin(), m_2.cend(),
		std::ostream_iterator < int > (std::cout, " "));
	std::cout << std::endl;

	std::cout << "set_union(): ";
	std::set_union(
		m_1.cbegin(), m_1.cend(),
		m_2.cbegin(), m_2.cend(),
		std::ostream_iterator < int > (std::cout, " "));
	std::cout << std::endl;

	std::cout << "set_intersection(): ";
	std::set_intersection(
		m_1.cbegin(), m_1.cend(),
		m_2.cbegin(), m_2.cend(),
		std::ostream_iterator < int >(std::cout, " "));
	std::cout << std::endl;

	std::cout << "set_difference(): ";
	std::set_difference(
		m_1.cbegin(), m_1.cend(),
		m_2.cbegin(), m_2.cend(),
		std::ostream_iterator < int >(std::cout, " "));
	std::cout << std::endl;

	std::cout << "set_symmetric_difference(): ";
	std::set_symmetric_difference(
		m_1.cbegin(), m_1.cend(),
		m_2.cbegin(), m_2.cend(),
		std::ostream_iterator < int >(std::cout, " "));
	std::cout << std::endl << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}