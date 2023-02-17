#include <vector>
#include <iostream>

template <typename T>
void print_size_and_cap(std::vector<T> vec)
{
	std::cout << vec.size() << "\t\t" << vec.capacity() << std::endl;
}

void task1()
{
	const size_t size = 9;
	std::vector<char> vec;

	std::cout << "Size\tCapacity" << std::endl;

	for (int i = 0; i < size; ++i)
	{
		vec.push_back(i);
		print_size_and_cap(vec);
	}

	std::cout << std::endl;
}

void task2()
{
	const size_t size = 3;
	const size_t elem = 10;
	std::vector<char> vec;

	vec.reserve(size);

	std::cout << "Size\tCapacity" << std::endl;

	for (int i = 0; i < size + elem; ++i)
	{
		vec.push_back(i);
		if (i > size)
			print_size_and_cap(vec);
	}

	std::cout << std::endl;
}

void task3()
{
	std::vector<char> vec(838521239);

	// vec.reserve(8385212392);
	// vec.reserve(8385212392 + 1); // bad_alloc
	// vec.max_size = 9223372036854775807

	print_size_and_cap(vec); //	838521239		838521239
	vec.push_back(0);
	print_size_and_cap(vec); //	838521240		838521240
}

int main(int argc, char const *argv[])
{
	// gcc version 11.3.0 (Ubuntu 11.3.0-1ubuntu1~22.04)

	task1();
	// сначала capacity=0, потом 1, затем каждый раз выделяется в 2 раза больше памяти (ёмкость -- всегда степень двойки)

	task2();
	// если задавать начальную ёмкость контейнера, то каждый раз при превышении размера она будет увеличиваться также в 2 раза. Но теперь это могут быть не только степени двойки, например 3, 6, 12, 24 ...

	task3();
	// если увеличить ёмкость в два раза система не позволяет, ёмкость увеличивается на 1


	return 0;
}