#include <deque>
#include <iostream>
#include <vector>

// =============================================================================

template < typename T >
void f(T value) // basic template
{
	std::cout << "f for T: " << value << std::endl;
}

template <>
void f<int>(int value) // full specialization for int
{
	std::cout << "f for int: " << value << std::endl;
}

void f(char value) // overload for char
{
	std::cout << "f overload for char: " << value << std::endl;
}

void f(double value) // overload for double
{
	std::cout << "f overload for double: " << value << std::endl;
}

void f(int value) // overload for double
{
	std::cout << "f overload for int: " << value << std::endl;
}

// =============================================================================

template < typename T1, typename T2 >
void g(T1 value_1, T2 value_2) // basic template
{
	std::cout << "g for T1, T2: " << value_1 << ", " << value_2 << std::endl;
}

// PARTIAL SPECIALIZATION DOESN'T WORK FOR FUNCTIONS
/*
template < typename T2 >
void g<int, T2>(int value_1, T2 value_2) // partial specialization for int, T2
{
	std::cout << "g for int, T2: " << value_1 << ", " << value_2 << std::endl;
}
*/

// =============================================================================

template < typename T1, typename T2 >
class X // basic template
{
public:
	void f() const 
	{ 
		std::cout << "f for T1, T2" << std::endl; 
	}
};

template < typename T >
class X < T, T > // partial specialization for T, T
{
public:
	void f() const 
	{ 
		std::cout << "f for T, T" << std::endl; 
	}
};

template < typename T1 >
class X < T1, int > // partial specialization for T2 == int
{
public:
	void f() const 
	{ 
		std::cout << "f for T1, int" << std::endl; 
	}
};

template < typename T1, typename T2 >
class X < T1*, T2* > // partial specialization for T1*, T2*
{
public:
	void f() const 
	{ 
		std::cout << "f for T1*, T2*" << std::endl; 
	}
};

template <>
class X < int, double > // full specialization for int and double
{
public:
	void f() const 
	{ 
		std::cout << "f for int, double" << std::endl; 
	}
};

// =============================================================================

template < typename T, std::size_t N = 128 >
class Container // basic template
{
public:
	void f() const
	{
		std::cout << "f for T, N = " << N << std::endl;
	}
};

template < std::size_t N >
class Container < std::string, N > // partial specialization for std::string, N
{
public:
	void f() const
	{
		std::cout << "f for std::string, N = " << N << std::endl;
	}
};

template <>
class Container < bool, 1024 > // full specialization for bool, 1024
{
public:
	void f() const
	{
		std::cout << "f for bool, N = 1024" << std::endl;
	}
};

// =============================================================================

int main()
{
	f(1.0);
	f(42);
	f <> (42);
	f <int> (42);
	f('a');
	f <> (1.0);
	f < double > (1.0);

	std::cout << std::endl;

	X < char, double > ().f();
	X < char, char   > ().f();
	X < double, int  > ().f();
	X < int*, long*  > ().f();
	X < int, double  > ().f();

	// X < int, int     > ().f(); // {T,T} or {T1,int}
	// X < int*, int*   > ().f(); // {T,T} or {T1*,T2*}

	std::cout << std::endl;

	Container < int             > ().f();
	Container < int, 42         > ().f();
	Container < std::string     > ().f();
	Container < std::string, 10 > ().f();
	Container < bool, 256       > ().f();
	Container < bool, 1024      > ().f();

	std::cout << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}