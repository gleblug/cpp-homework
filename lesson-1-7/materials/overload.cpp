#include <iostream>

int && xvalue_func();
int & lvalue_func();
int prvalue_func();
const int const_prvalue_func();
void foo(int & arg);
void foo(const int & arg);
void foo(int && arg);
void foo(const int && arg);

int main(int argc, char ** argv)
{
	const int i = 0;
	
	foo(xvalue_func());
	foo(lvalue_func());
	foo(prvalue_func());
	foo(const_prvalue_func());
	foo(i);
	foo(5);

	system("pause");

	return EXIT_SUCCESS;
}

void foo(int & arg)
{
	std::cout << "void foo(int & arg)" << std::endl;
}

void foo(const int & arg)
{
	std::cout << "void foo(const int & arg)" << std::endl;
}

void foo(int && arg)
{
	std::cout << "void foo(int && arg)" << std::endl;
}

void foo(const int && arg)
{
	std::cout << "void foo(const int && arg)" << std::endl;
}

int && xvalue_func()
{
	return 5;
}

int & lvalue_func()
{
	static int i = 0;
	return i;
}

int prvalue_func()
{
	return 5;
}

const int const_prvalue_func()
{
	return 5;
}